#pragma once

#include <string>

class lzo
{
public:
	static std::string compress(const void* src, int slen);
	static std::string decompress(const void* src, int slen);
};