#include <Helpers/Macro.h>
#include <Drawing.h>
#include <CINI.h>
#include <CFinalSunDlg.h>
#include <CFinalSunApp.h>
#include <CMapData.h>
#include <CPalette.h>
#include <CObjectDatas.h>
#include <CTileTypeClass.h>
#include <CIsoView.h>

#include <MFC/ppmfc_cstring.h>

#include "../FA2sp.h"

// FA2 will no longer automatically change the extension of map
DEFINE_HOOK(42700A, CFinalSunDlg_SaveMap_Extension, 9)
{
	return 0x42708D;
}

// Extend Undo/Redo limit
DEFINE_HOOK(4BBAB8, CMapData_SaveUndoRedoData_SizeLimit, 6)
{
	++CMapData::Instance->UndoRedoCurrentDataIndex;
	++CMapData::Instance->UndoRedoDataCount;

	R->ESI(CMapData::Instance->UndoRedoDataCount);

	if (CMapData::Instance->UndoRedoDataCount <= ExtConfigs::UndoRedoLimit)
		return 0x4BBBB7;

	R->EDX(CMapData::Instance->UndoRedoData);
	CMapData::Instance->UndoRedoDataCount = ExtConfigs::UndoRedoLimit;
	CMapData::Instance->UndoRedoCurrentDataIndex = ExtConfigs::UndoRedoLimit - 1;
	return 0x4BBAF7;
}

// Self explained nameing
DEFINE_HOOK(421B70, CFinalSunApp_InitInstance_NoEasyViewExplain, 5)
{
	CFinalSunApp::Instance->EasyMode = false;

	return 0x421EEB;
}

// Fix bug for incorrect color while drawing
DEFINE_HOOK(468760, Miscs_GetColor, 7)
{
	GET_STACK(const char*, pHouse, 0x4);
	GET_STACK(const char*, pColor, 0x8);

	ppmfc::CString color = "";
	if (pHouse)
		if (auto pStr = Variables::Rules.TryGetString(pHouse, "Color"))
			color = *pStr;

	if (pColor)
		color = pColor;

	HSVClass hsv{ 0,0,0 };
	if (!color.IsEmpty())
		if (auto const ppValue = CINI::Rules->TryGetString("Colors", color))
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

// Fix the bug that up&down&left&right vk doesn't update the TileSetBrowserView
DEFINE_HOOK(422EA4, CFinalSunApp_ProcessMessageFilter_UpdateTileSetBrowserView_UpAndDown, 8)
{
	CFinalSunDlg::Instance->MyViewFrame.pTileSetBrowserFrame->View.SelectTileSet(
		(*CTileTypeClass::CurrentTileType)[CIsoView::CurrentCommand->Type].TileSet,
		false
	);

	return 0;
}

DEFINE_HOOK_AGAIN(422BF6, CFinalSunApp_ProcessMessageFilter_UpdateTileSetBrowserView_LeftAndRight, 7) // VirtualKey_Right
DEFINE_HOOK(422B95, CFinalSunApp_ProcessMessageFilter_UpdateTileSetBrowserView_LeftAndRight, 7) // VirtualKey_Left
{
	CFinalSunDlg::Instance->MyViewFrame.pTileSetBrowserFrame->View.RedrawWindow(
		nullptr, nullptr, 
		RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW
	);

	return 0;
}

//
//DEFINE_HOOK(4C61C5, CMapData_ResizeMap_PositionFix, 5)
//{
//	GET(CellData*, pCell, EAX);
//	auto const pSrc = CONTAINING_RECORD(R->ECX(), CellData, Flag);
//
//	pCell->Smudge = pSrc->Smudge;
//	pCell->SmudgeType = pSrc->SmudgeType;
//	pCell->BaseNode = pSrc->BaseNode;
//
//	return 0;
//}