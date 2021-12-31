#pragma once

#include <vector>

struct InfoStruct
{
	unsigned short Ramp;
	unsigned short Morphable;
	unsigned short RampIndex;
	unsigned short MorphableIndex;
};

class TheaterInfo
{
public:
	static const char* GetInfoSection();
	static void UpdateTheaterInfo();

	static std::vector<InfoStruct> CurrentInfo;
};