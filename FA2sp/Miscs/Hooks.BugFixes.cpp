#include <Helpers/Macro.h>
#include <Drawing.h>
#include <GlobalVars.h>
#include <CINI.h>
#include <CMapData.h>
#include <CPalette.h>
#include <CObjectDatas.h>

#include <MFC/ppmfc_cstring.h>

#include "../FA2sp.h"

// FA2 will no longer automatically change the extension of map
DEFINE_HOOK(42700A, CFinalSunDlg_SaveMap_Extension, 9)
{
	return 0x42708D;
}

// Make FA2 use path stored in FinalAlert.ini instead of Reg
DEFINE_HOOK(41FD8A, CFinalSunDlg_GetFilePath_1, 6)
{
	return 0x41FD90;
}

DEFINE_HOOK(41FDDB, CFinalSunDlg_GetFilePath_2, 6)
{
	return 0x41FDE9;
}

// Extend Undo/Redo limit
DEFINE_HOOK(4BBAB8, CMapData_sub_4BB990, 6)
{
	GET(CMapData*, pThis, EBX);

	++pThis->UndoRedoCurrentDataIndex;
	++pThis->UndoRedoDataCount;

	R->ESI(pThis->UndoRedoDataCount);

	if (pThis->UndoRedoDataCount <= ExtConfigs::UndoRedoLimit)
		return 0x4BBBB7;

	R->EDX(pThis->UndoRedoData);
	pThis->UndoRedoDataCount = ExtConfigs::UndoRedoLimit;
	pThis->UndoRedoCurrentDataIndex = ExtConfigs::UndoRedoLimit - 1;
	return 0x4BBAF7;
}


// Self explained nameing
DEFINE_HOOK(421BCE, CFinalSunApp_InitInstance_NoEasyViewExplain, 6)
{
	return 0x421DBD;
}

// Fix bug for incorrect color while drawing
DEFINE_HOOK(468760, Miscs_GetColor, 7)
{
	GET_STACK(const char*, pHouse, 0x4);
	GET_STACK(const char*, pColor, 0x8);

	ppmfc::CString color = "";
	if (pHouse)
		if (auto pStr = GlobalVars::INIFiles::CurrentDocument->TryGetString(pHouse, "Color"))
			color = *pStr;

	if (pColor)
		color = pColor;

	HSVClass hsv{ 0,0,0 };
	if (!color.IsEmpty())
		if (auto const ppValue = GlobalVars::INIFiles::Rules->TryGetString("Colors", color))
			sscanf_s(*ppValue, "%hhu,%hhu,%hhu", &hsv.H, &hsv.S, &hsv.V);

	RGBClass rgb;
	if (!ExtConfigs::UseRGBHouseColor)
		rgb = hsv;
	else
		rgb = { hsv.H,hsv.S,hsv.V };

	R->EAX<int>(rgb);

	return 0x468EEB;
}

// https://modenc.renegadeprojects.com/Cell_Spots
DEFINE_HOOK(473E66, CIsoView_Draw_InfantrySubcell, B)
{
	GET(int, nX, EDI);
	GET(int, nY, ESI);
	REF_STACK(CInfantryData, infData, STACK_OFFS(0xD18, 0x78C));

	int nSubcell;
	sscanf_s(infData.SubCell, "%d", &nSubcell);
	switch (nSubcell)
	{
	case 2:
		R->EDI(nX + 15);
		break;
	case 3:
		R->EDI(nX - 15);
		break;
	case 4:
		R->ESI(nY - 7);
		break;
	case 0:
	case 1:
	default:
		break;
	}

	return 0x473E8C;
}