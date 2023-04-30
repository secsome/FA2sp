#include "lcw.h"

std::string lcw::compress(const void* src, int slen)
{
	std::string ret;

	unsigned char* ptr = (unsigned char*)src;
	char* buffer = new char[BufferSize];

	while (slen > 0)
	{
		const int blocksize = std::min(slen, BlockSize);
		const int count = LCW_Compress(ptr, buffer + 4, blocksize);
		reinterpret_cast<unsigned short*>(buffer)[0] = count;
		reinterpret_cast<unsigned short*>(buffer)[1] = blocksize;
		ret.append(buffer, count + 4);
		ptr += blocksize;
		slen -= blocksize;
	}

	delete[] buffer;

	return ret;
}

std::string lcw::decompress(const void* src, int slen)
{
	std::string ret;

	unsigned char* ptr = (unsigned char*)src;
	char* buffer = new char[BufferSize];

	while (slen > 0)
	{
		auto blocksize = reinterpret_cast<unsigned short*>(ptr)[0];
		auto count = LCW_Uncompress(ptr + 4, buffer);
		ret.append(buffer, count);
		ptr += blocksize;
		slen -= blocksize;
	}

	delete[] buffer;

	return ret;
}