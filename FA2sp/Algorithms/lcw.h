#pragma once

#include <string>

class lcw
{
public:
	static std::string compress(const void* src, int slen);
	static std::string decompress(const void* src, int slen);

private:
	static constexpr int LCW_Worst_Case(int datasize) 
	{
		return datasize + (datasize / 63) + 1;
	}

	static constexpr int BlockSize = 1024 * 8;
	static constexpr int SafetyMargin = BlockSize / 128 + 1;
	static constexpr int BufferSize = BlockSize + SafetyMargin;

	static unsigned int __cdecl LCW_Uncompress(void* source, void* dest, unsigned int length = 0);
	static int __cdecl LCW_Compress(void const* source, void* dest, unsigned int length);
};
