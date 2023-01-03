#include "lcw.h"

int lcw::LCW_Compress(void const* input, void* output, unsigned int size)
{
	bool relative = size > UINT16_MAX ? true : false;

	if (!size || !input || !output) {
		return 0;
	}

	const unsigned char* getp = static_cast<const unsigned char*>(input);
	unsigned char* putp = static_cast<unsigned char*>(output);
	const unsigned char* getstart = getp;
	const unsigned char* getend = getp + size;
	unsigned char* putstart = putp;

	//relative LCW starts with 0 as flag to decoder.
	//this is only used by later games for decoding hi-color vqa files
	if (relative) {
		*putp++ = 0;
	}

	//Implementations that properly conform to the WestWood encoder should
	//write a starting cmd1. Its important for using the offset copy commands
	//to do more efficient RLE in some cases than the cmd4.

	//we also set bool to flag that we have an on going cmd1.
	unsigned char* cmd_onep = putp;
	*putp++ = 0x81;
	*putp++ = *getp++;
	bool cmd_one = true;

	//Compress data until we reach end of input buffer.
	while (getp < getend) {
		//Is RLE encode (4bytes) worth evaluating?
		if (getend - getp > 64 && *getp == *(getp + 64)) {
			//RLE run length is encoded as a short so max is UINT16_MAX
			const unsigned char* rlemax = (getend - getp) < UINT16_MAX ? getend : getp + UINT16_MAX;
			const unsigned char* rlep;

			for (rlep = getp + 1; *rlep == *getp && rlep < rlemax; ++rlep);

			unsigned short run_length = rlep - getp;

			//If run length is long enough, write the command and start loop again
			if (run_length >= 0x41) {
				//write 4byte command 0b11111110
				cmd_one = false;
				*putp++ = 0xFE;
				*putp++ = run_length;
				*putp++ = run_length >> 8;
				*putp++ = *getp;
				getp = rlep;
				continue;
			}
		}

		//current block size for an offset copy
		int block_size = 0;
		const unsigned char* offstart;

		//Set where we start looking for matching runs.
		if (relative) {
			offstart = (getp - getstart) < UINT16_MAX ? getstart : getp - UINT16_MAX;
		}
		else {
			offstart = getstart;
		}

		//Look for matching runs
		const unsigned char* offchk = offstart;
		const unsigned char* offsetp = getp;
		while (offchk < getp) {
			//Move offchk to next matching position
			while (offchk < getp && *offchk != *getp) {
				++offchk;
			}

			//If the checking pointer has reached current pos, break
			if (offchk >= getp) {
				break;
			}

			//find out how long the run of matches goes for
			int i;
			for (i = 1; &getp[i] < getend; ++i) {
				if (offchk[i] != getp[i]) {
					break;
				}
			}

			if (i >= block_size) {
				block_size = i;
				offsetp = offchk;
			}

			++offchk;
		}

		//decide what encoding to use for current run
		//If its less than 2 bytes long, we store as is with cmd1
		if (block_size <= 2) {
			//short copy 0b10??????
			//check we have an existing 1 byte command and if its value is still
			//small enough to handle additional bytes
			//start a new command if current one doesn't have space or we don't
			//have one to continue
			if (cmd_one && *cmd_onep < 0xBF) {
				//increment command value
				++* cmd_onep;
				*putp++ = *getp++;
			}
			else {
				cmd_onep = putp;
				*putp++ = 0x81;
				*putp++ = *getp++;
				cmd_one = true;
			}
			//Otherwise we need to decide what relative copy command is most efficient
		}
		else {
			unsigned short offset;
			unsigned short rel_offset = getp - offsetp;
			if (block_size > 0xA || ((rel_offset) > 0xFFF)) {
				//write 5 byte command 0b11111111
				if (block_size > 0x40) {
					*putp++ = 0xFF;
					*putp++ = block_size;
					*putp++ = block_size >> 8;
					//write 3 byte command 0b11??????
				}
				else {
					*putp++ = (block_size - 3) | 0xC0;
				}

				offset = relative ? rel_offset : offsetp - getstart;
				//write 2 byte command? 0b0???????
			}
			else {
				offset = rel_offset << 8 | (16 * (block_size - 3) + (rel_offset >> 8));
			}
			*putp++ = offset;
			*putp++ = offset >> 8;
			getp += block_size;
			cmd_one = false;
		}
	}

	//write final 0x80, basically an empty cmd1 to signal the end of the stream.
	*putp++ = 0x80;

	//return the size of the compressed data.
	return putp - putstart;
}

