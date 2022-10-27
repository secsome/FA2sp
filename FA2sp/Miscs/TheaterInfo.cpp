#include "TheaterInfo.h"

#include <Helpers/Macro.h>

#include <CTileTypeClass.h>
#include <CLoading.h>
#include <CMapData.h>
#include <CINI.h>

#include <vector>

#include "../Helpers/STDHelpers.h"

const char* TheaterInfo::GetInfoSection()
{
	switch (CLoading::Instance->TheaterIdentifier)
	{
	case 'A':
		return "SnowInfo";
	case 'U':
		return "UrbanInfo";
	case 'D':
		return "DesertInfo";
	case 'L':
		return "LunarInfo";
	case 'N':
		return "NewUrbanInfo";
	case 'T':
	default:
		return "TemperateInfo";
	}
}

void TheaterInfo::UpdateTheaterInfo()
{
	CurrentInfo.clear();
	auto const pSection = GetInfoSection();
	ppmfc::CString buffer = CINI::FAData->GetString(pSection, "Morphables");
	buffer.Trim();
	for (auto& str : STDHelpers::SplitString(buffer))
	{
		CurrentInfo.emplace_back(InfoStruct());
		CurrentInfo.back().Morphable = atoi(str);
		CurrentInfo.back().MorphableIndex = CTileTypeClass::GetTileIndex(CurrentInfo.back().Morphable);
	}
	buffer = CINI::FAData->GetString(pSection, "Ramps");
	buffer.Trim();
	int i = 0;
	for (auto& str : STDHelpers::SplitString(buffer))
	{
		CurrentInfo[i].Ramp = atoi(str);
		CurrentInfo[i].RampIndex = CTileTypeClass::GetTileIndex(CurrentInfo[i].Ramp);
		++i;
	}

}
std::vector<InfoStruct> TheaterInfo::CurrentInfo;

DEFINE_HOOK(49D121, CMapData_UpdateINIFile_UpdateTheaterInfos, 7)
{
	TheaterInfo::UpdateTheaterInfo();
	return 0;
}

DEFINE_HOOK(45BE1D, CIsoView_OnMouseMove_TheaterInfo, 5)
{
	GET(CTileTypeClass*, pTile, EBP);
	GET(const int, nRampType, EBX);
	GET(int, nRampIndex, EDI);
	GET_STACK(unsigned int, nIndex, STACK_OFFS(0x3D544, 0x3D530));

	if (nRampType == -1)
	{
		for (auto& info : TheaterInfo::CurrentInfo)
			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
				if (pTile->Morphable)
				{
					CMapData::Instance->SetTileAt(nIndex, info.MorphableIndex);
					break;
				}
	}

	if (pTile->Morphable && nRampType != -1)
	{
		for (auto& info : TheaterInfo::CurrentInfo)
			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
			{
				nRampIndex = info.RampIndex;
				break;
			}

		CMapData::Instance->SetTileAt(nIndex, nRampIndex + nRampType - 1);
	}	return 0x45BEAF;
}

DEFINE_HOOK(45E0CB, CMapData_sub_45D090_TheaterInfo_1, 6)
{
	GET_STACK(CTileTypeClass*, pTile, STACK_OFFS(0xF8, 0xAC));
	GET_STACK(const int, nRampType, STACK_OFFS(0xF8, 0xE0));

	enum { LABEL_290 = 0x45E7A6, HasInfo = 0x45E117 };

	if (nRampType != -1 || !pTile->Morphable)
		return LABEL_290;
	
	for (auto& info : TheaterInfo::CurrentInfo)
		if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
		{
			R->EAX(info.MorphableIndex);
			return HasInfo;
		}

	return LABEL_290;
}

// LABEL_290
DEFINE_HOOK(45E7A6, CMapData_sub_45D090_TheaterInfo_2, 7)
{
	GET_STACK(CTileTypeClass*, pTile, STACK_OFFS(0xF8, 0xAC));
	GET_STACK(const int, nRampType, STACK_OFFS(0xF8, 0xE0));
	GET_STACK(int, nRampIndex, STACK_OFFS(0xF8, 0x20));
	GET_STACK(const int, nIndex, STACK_OFFS(0xF8, -0x4));

	if (pTile->Morphable && nRampType != -1)
	{
		nRampIndex = R->Stack<int>(STACK_OFFS(0xF8, 0x20));
		for (auto& info : TheaterInfo::CurrentInfo)
			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
			{
				nRampIndex = info.RampIndex;
				break;
			}

		CMapData::Instance->SetTileAt(nIndex, nRampIndex + nRampType - 1);
	}

	return 0x45E801;
}
//
//DEFINE_HOOK(46BB36, CMapData_sub_46AB30_TheaterInfo, A)
//{
//	GET(CTileTypeClass*, pTile, EBP);
//	GET(const int, nRampType, EBX);
//	GET(int, nRampIndex, EDI);
//	GET(const int, nIndex, ESI);
//
//	enum { LABEL_320 = 0x46BBC2 };
//
//	if (nRampType == -1)
//	{
//		for (auto& info : TheaterInfo::CurrentInfo)
//			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
//			{
//				if (!pTile->Morphable)
//					return LABEL_320;
//				CMapData::Instance->sub_416550(nIndex, info.MorphableIndex);
//				break;
//			}
//	}
//
//	if (pTile->Morphable && nRampType != -1)
//	{
//		for (auto& info : TheaterInfo::CurrentInfo)
//			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
//			{
//				nRampIndex = info.RampIndex;
//				break;
//			}
//
//		CMapData::Instance->sub_416550(nIndex, nRampIndex + nRampType - 1);
//	}
//
//	return LABEL_320;
//}

DEFINE_HOOK_AGAIN(4662E8, CIsoView_OnLButtonDown_TheaterInfo, 5)
DEFINE_HOOK_AGAIN(465BBF, CIsoView_OnLButtonDown_TheaterInfo, 5)
DEFINE_HOOK_AGAIN(46547C, CIsoView_OnLButtonDown_TheaterInfo, 5)
DEFINE_HOOK(4649D0, CIsoView_OnLButtonDown_TheaterInfo, 5)
{
	GET(CTileTypeClass*, pTile, EDI);
	GET(int, nRampType, ECX);
	GET(int, nRampIndex, EBX);

	GET_BASE(const int, nIndex, R->Origin() == 0x46547C || R->Origin() == 0x4649D0 ? 0x10 : 0x14);

	if (nRampType == -1)
	{
		for (auto& info : TheaterInfo::CurrentInfo)
			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
				if (pTile->Morphable)
				{
					CMapData::Instance->SetTileAt(nIndex, info.MorphableIndex);
					nRampType = R->Base<int>(0x8);
					break;
				}
	}

	if (pTile->Morphable && nRampType != -1)
	{
		for (auto& info : TheaterInfo::CurrentInfo)
			if (info.Ramp == pTile->TileSet || info.Morphable == pTile->TileSet)
			{
				nRampIndex = info.RampIndex;
				break;
			}

		CMapData::Instance->SetTileAt(nIndex, nRampIndex + nRampType - 1);
	}

	return R->Origin() + 0x91;
}

