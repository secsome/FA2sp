#include "Body.h"
#include "../../FA2sp.h"

#include <Drawing.h>
#include <CINI.h>
#include <CMapData.h>

#include <Windows.h>

#include "../CLoading/Body.h"
#include "../../Helpers/STDHelpers.h"

DEFINE_HOOK(45AF03, CIsoView_StatusBar_YXTOXY_YToX_1, 7)
{
	GET_STACK(int, nPointX, 0x30);
	R->EDI(nPointX);
	R->ECX(R->lea_Stack<DWORD>(0x458));
	return 0x45AF0A;
}

DEFINE_HOOK(45AF21, CIsoView_StatusBar_YXTOXY_YToX_2, 7)
{
	GET_STACK(int, nPointY, 0x38);
	R->EDI(nPointY);
	return 0;
}

DEFINE_HOOK(45AF44, CIsoView_StatusBar_YXTOXY_XToY_1, 7)
{
	GET_STACK(int, nPointY, 0x38);
	R->EBX(nPointY);
	R->EAX(R->lea_Stack<DWORD>(0x458));
	return 0x45AF4B;
}

DEFINE_HOOK(45AF57, CIsoView_StatusBar_YXTOXY_XToY_2, 7)
{
	GET_STACK(int, nPointX, 0x30);
	R->EBX(nPointX);
	return 0;
}

// Fix on wrong infantry facing
DEFINE_HOOK(473E46, CIsoView_UpdatePaint_InfantryFacing, 9)
{
	GET(int, Facing, EAX);
	R->EAX(7 - Facing / 32);
	R->ECX(R->lea_Stack<DWORD>(0x590));
	return 0x473E52;
}

DEFINE_HOOK(46CB96, CIsoView_UpdateOverlay_AutoConnect_1, 5)
{
	// static int __stdcall sub_469B20(int Y, int X);
	int X = R->EBX();
	int Y = R->EBP();
	PUSH_VAR32(X);
	PUSH_VAR32(Y);
	CALL(0x469B20);
	return 0x46CBD3;
}

DEFINE_HOOK(469A69, CIsoView_UpdateOverlay_AutoConnect_2, 8)
{
	GET(unsigned char, nOverlayIndex, ESI);
	GET(bool, bConnectAsWall, ECX);
	if (bConnectAsWall)
		return 0x469A71;
	if (nOverlayIndex >= 0 && nOverlayIndex <= 255)
	{
		auto& rules = CINI::Rules();
		ppmfc::CString key;
		key.Format("%d", nOverlayIndex);
		auto pRegName = rules.GetString("OverlayTypes", key, "");
		bool bWall = rules.GetBool(pRegName, "Wall", false);
		if (bWall)
			return 0x469A71;
	}
	return 0x469B07;
}

DEFINE_HOOK(459F4F, CIsoView_Draw_CopySelectionBoundColor, 6)
{
	R->Stack<COLORREF>(0x0, ExtConfigs::CopySelectionBound_Color);
	return 0;
}

DEFINE_HOOK(45AD81, CIsoView_Draw_CursorSelectionBoundColor, 5)
{
	R->Stack<COLORREF>(0x0, ExtConfigs::CursorSelectionBound_Color);
	return 0;
}

DEFINE_HOOK(45ADD0, CIsoView_Draw_CursorSelectionBoundHeightColor, 6)
{
	R->Stack<COLORREF>(0x8, ExtConfigs::CursorSelectionBound_HeightColor);
	return 0;
}

//DEFINE_HOOK(474A49, CIsoView_Draw_WaypointColor, 5)
//{
//	GET(CIsoView*, pThis, EBP);
//	GET(int, X, ESI);
//	GET(int, Y, EDI);
//	REF_STACK(ppmfc::CString, str, STACK_OFFS(0xD18, 0xCE4));
//
//	pThis->DrawText(X + 15, Y + 7, str, ExtConfigs::Waypoint_Color);
//
//	return 0x474A67;
//}

DEFINE_HOOK(470194, CIsoView_Draw_LayerVisible_Overlay, 8)
{
	return CIsoViewExt::DrawOverlays ? 0 : 0x470772;
}

DEFINE_HOOK(470772, CIsoView_Draw_LayerVisible_Structures, 8)
{
	return CIsoViewExt::DrawStructures ? 0 : 0x4725CB;
}

DEFINE_HOOK(4725CB, CIsoView_Draw_LayerVisible_Basenodes, 8)
{
	return CIsoViewExt::DrawBasenodes ? 0 : 0x472F33;
}

DEFINE_HOOK(472F33, CIsoView_Draw_LayerVisible_Units, 9)
{
	return CIsoViewExt::DrawUnits ? 0 : 0x47371A;
}

DEFINE_HOOK(47371A, CIsoView_Draw_LayerVisible_Aircrafts, 9)
{
	return CIsoViewExt::DrawAircrafts ? 0 : 0x473DA0;
}

DEFINE_HOOK(473DAA, CIsoView_Draw_LayerVisible_Infantries, 9)
{
	return CIsoViewExt::DrawInfantries ? 0 : 0x4741D9;
}

DEFINE_HOOK(4741E7, CIsoView_Draw_LayerVisible_Terrains, 9)
{
	return CIsoViewExt::DrawTerrains ? 0 : 0x474563;
}

DEFINE_HOOK(474563, CIsoView_Draw_LayerVisible_Smudges, 9)
{
	return CIsoViewExt::DrawSmudges ? 0 : 0x4748DC;
}

//DEFINE_HOOK(4748DC, CIsoView_Draw_LayerVisible_Celltags, 9)
//{
//	return CIsoViewExt::DrawCelltags ? 0 : 0x474986;
//}
//
//DEFINE_HOOK(474986, CIsoView_Draw_LayerVisible_Waypoints, 9)
//{
//	return CIsoViewExt::DrawWaypoints ? 0 : 0x474A91;
//}
//
//DEFINE_HOOK(474B9D, CIsoView_Draw_LayerVisible_Tubes, 9)
//{
//	return CIsoViewExt::DrawTubes ? 0 : 0x474D64;
//}

DEFINE_HOOK(474DDF, CIsoView_Draw_LayerVisible_Bounds, 5)
{
	return CIsoViewExt::DrawBounds ? 0 : 0x474FE0;
}

DEFINE_HOOK(474FE0, CIsoView_Draw_LayerVisible_MoneyOnMap, 7)
{
	return CIsoViewExt::DrawMoneyOnMap ? 0 : 0x4750B0;
}

DEFINE_HOOK(471162, CIsoView_Draw_PowerUp1Loc_PosFix, 5)
{
	REF_STACK(const ppmfc::CString, ID, STACK_OFFS(0xD18, 0xBFC));
	REF_STACK(const ppmfc::CString, BldID, STACK_OFFS(0xD18, 0xC08));
	GET_STACK(int, X, STACK_OFFS(0xD18, 0xCFC));
	GET_STACK(int, Y, STACK_OFFS(0xD18, 0xD00));

	auto pBldData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(BldID, 0));
	auto pData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(ID, 0));

	ppmfc::CString ArtID; // BldArtID
	if (auto ppImage = Variables::Rules.TryGetString(BldID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = BldID;

	X += CINI::Art->GetInteger(ArtID, "PowerUp1LocXX", 0);
	Y += CINI::Art->GetInteger(ArtID, "PowerUp1LocYY", 0);

	X += (pBldData->FullWidth - pData->FullWidth) / 2;
	Y += (pBldData->FullHeight - pData->FullHeight) / 2;

	R->ESI(X);
	R->EDI(Y);

	return 0x47141D;
}

DEFINE_HOOK(471980, CIsoView_Draw_PowerUp2Loc_PosFix, 5)
{
	REF_STACK(const ppmfc::CString, ID, STACK_OFFS(0xD18, 0xBFC));
	REF_STACK(const ppmfc::CString, BldID, STACK_OFFS(0xD18, 0xC08));
	GET_STACK(int, X, STACK_OFFS(0xD18, 0xCFC));
	GET_STACK(int, Y, STACK_OFFS(0xD18, 0xD00));

	auto pBldData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(BldID, 0));
	auto pData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(ID, 0));

	ppmfc::CString ArtID; // BldArtID
	if (auto ppImage = Variables::Rules.TryGetString(BldID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = BldID;

	X += CINI::Art->GetInteger(ArtID, "PowerUp2LocXX", 0);
	Y += CINI::Art->GetInteger(ArtID, "PowerUp2LocYY", 0);

	X += (pBldData->FullWidth - pData->FullWidth) / 2;
	Y += (pBldData->FullHeight - pData->FullHeight) / 2;

	R->ESI(X);
	R->EDI(Y);

	return 0x471BB8;
}

DEFINE_HOOK(4720D3, CIsoView_Draw_PowerUp3Loc_PosFix, 5)
{
	REF_STACK(const ppmfc::CString, ID, STACK_OFFS(0xD18, 0xBFC));
	REF_STACK(const ppmfc::CString, BldID, STACK_OFFS(0xD18, 0xC08));
	GET_STACK(int, X, STACK_OFFS(0xD18, 0xCFC));
	GET_STACK(int, Y, STACK_OFFS(0xD18, 0xD00));

	auto pBldData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(BldID, 0));
	auto pData = ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(ID, 0));

	ppmfc::CString ArtID; // BldArtID
	if (auto ppImage = Variables::Rules.TryGetString(BldID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = BldID;

	X += CINI::Art->GetInteger(ArtID, "PowerUp3LocXX", 0);
	Y += CINI::Art->GetInteger(ArtID, "PowerUp3LocYY", 0);

	X += (pBldData->FullWidth - pData->FullWidth) / 2;
	Y += (pBldData->FullHeight - pData->FullHeight) / 2;

	R->ESI(X);
	R->EDI(Y);

	return 0x47230B;
}

DEFINE_HOOK(470986, CIsoView_Draw_BuildingImageDataQuery_1, 8)
{
	REF_STACK(ImageDataClass, image, STACK_OFFS(0xD18, 0xAFC));
	REF_STACK(StructureData, structure, STACK_OFFS(0xD18, 0xC0C));

	int nFacing = 0;
	if (Variables::Rules.GetBool(structure.ID, "Turret"))
		nFacing = 7 - (structure.Facing / 32) % 8;
	image = *ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(structure.ID, nFacing));

	return 0x4709E1;
}

DEFINE_HOOK(470AE3, CIsoView_Draw_BuildingImageDataQuery_2, 7)
{
	REF_STACK(ImageDataClass, image, STACK_OFFS(0xD18, 0xAFC));
	REF_STACK(StructureData, structure, STACK_OFFS(0xD18, 0xC0C));

	int nFacing = 0;
	if (Variables::Rules.GetBool(structure.ID, "Turret"))
		nFacing = (7 - structure.Facing / 32) % 8;
	image = *ImageDataMapHelper::GetImageDataFromMap(CLoadingExt::GetImageName(structure.ID, nFacing));

	return 0x470B4D;
}

DEFINE_HOOK(4709EE, CIsoView_Draw_ShowBuildingOutline, 6)
{
	GET(CIsoViewExt*, pThis, EDI);
	GET(int, X, EBX);
	GET(int, Y, EBP);
	GET_STACK(int, W, STACK_OFFS(0xD18, 0xCFC));
	GET_STACK(int, H, STACK_OFFS(0xD18, 0xD00));
	GET_STACK(COLORREF, dwColor, STACK_OFFS(0xD18, 0xD04));
	LEA_STACK(LPDDSURFACEDESC2, lpDesc, STACK_OFFS(0xD18, 0x92C));

	pThis->DrawLockedCellOutline(X, Y, W, H, dwColor, false, false, lpDesc);

	return 0x470A38;
}

DEFINE_HOOK(47280B, CIsoView_Draw_BasenodeOutline, 6)
{
	GET_STACK(CIsoViewExt*, pThis, STACK_OFFS(0xD18, 0xCD4));
	GET(int, X, EBX);
	GET(int, Y, EBP);
	GET_STACK(int, W, STACK_OFFS(0xD18, 0xCFC));
	GET_STACK(int, H, STACK_OFFS(0xD18, 0xD00));
	GET_STACK(COLORREF, dwColor, STACK_OFFS(0xD18, 0xB94));
	LEA_STACK(LPDDSURFACEDESC2, lpDesc, STACK_OFFS(0xD18, 0x92C));

	pThis->DrawLockedCellOutline(X, Y, W, H, dwColor, true, false, lpDesc);
	pThis->DrawLockedCellOutline(X + 1, Y, W, H, dwColor, true, false, lpDesc);

	return 0x472884;
}

DEFINE_HOOK(4748DC, CIsoView_Draw_SkipCelltagAndWaypointDrawing, 9)
{
	return 0x474A91;
}

DEFINE_HOOK(474AE3, CIsoView_Draw_DrawCelltagAndWaypointAndTube_EarlyUnlock, 6)
{
	GET_STACK(CIsoViewExt*, pThis, STACK_OFFS(0xD18, 0xCD4));

	pThis->lpDDBackBufferSurface->Unlock(nullptr);

	return pThis ? 0x474AEF : 0x474DB3;
}

DEFINE_HOOK(474B9D, CIsoView_Draw_DrawCelltagAndWaypointAndTube_DrawStuff, 9)
{
	GET_STACK(CIsoViewExt*, pThis, STACK_OFFS(0xD18, 0xCD4));
	REF_STACK(CellData, celldata, STACK_OFFS(0xD18, 0xC60));
	int X = R->Stack<int>(STACK_OFFS(0xD18, 0xCE4)) - R->Stack<float>(STACK_OFFS(0xD18, 0xCB0));
	int Y = R->Stack<int>(STACK_OFFS(0xD18, 0xCD0)) - R->Stack<float>(STACK_OFFS(0xD18, 0xCB8));

	// We had unlocked it already, just blt them now
	if (CIsoViewExt::DrawCelltags && celldata.CellTag != -1)
		pThis->DrawCelltag(X, Y);
	if (CIsoViewExt::DrawWaypoints && celldata.Waypoint != -1)
		pThis->DrawWaypointFlag(X, Y);
	if (CIsoViewExt::DrawTubes && celldata.Tube != -1)
		pThis->DrawTube(&celldata, X, Y);

	return 0x474D64;
}

DEFINE_HOOK(474DB7, CIsoView_Draw_DrawCelltagAndWaypointAndTube_SkipOriginUnlock, 6)
{
	GET(CIsoViewExt*, pThis, EBX);

	R->EAX(pThis->lpDDBackBufferSurface);
	R->EBP(&pThis->lpDDBackBufferSurface);

	return 0x474DCE;
}

DEFINE_HOOK(474DDF, CIsoView_Draw_WaypointTexts, 5)
{
	if (CIsoViewExt::DrawWaypoints)
	{
		GET(CIsoViewExt*, pThis, EBX);

		GET_STACK(HDC, hDC, STACK_OFFS(0xD18, 0xC68));
		GET_STACK(int, jMin, STACK_OFFS(0xD18, 0xC10));
		GET_STACK(int, iMin, STACK_OFFS(0xD18, 0xCBC));
		GET_STACK(const int, jMax, STACK_OFFS(0xD18, 0xC64));
		GET_STACK(const int, iMax, STACK_OFFS(0xD18, 0xC18));

		SetTextColor(hDC, ExtConfigs::Waypoint_Color);
		if (ExtConfigs::Waypoint_Background)
		{
			SetBkMode(hDC, OPAQUE);
			SetBkColor(hDC, ExtConfigs::Waypoint_Background_Color);
		}
		else
			SetBkMode(hDC, TRANSPARENT);
		SetTextAlign(hDC, TA_CENTER);

		auto pSection = CINI::CurrentDocument->GetSection("Waypoints");
		for (int j = jMin; j < jMax; ++j)
		{
			for (int i = iMin; i < iMax; ++i)
			{
				int Y = j, X = i;

				pThis->MapCoord2ScreenCoord(Y, X);
				auto pCell = CMapData::Instance->TryGetCellAt(i, j);

				int drawX = Y - R->Stack<float>(STACK_OFFS(0xD18, 0xCB0)) + 30;
				int drawY = X - R->Stack<float>(STACK_OFFS(0xD18, 0xCB8)) - 15;

				if (pCell->Waypoint != -1)
				{
					auto pWP = *pSection->GetKeyAt(pCell->Waypoint);
					TextOut(hDC, drawX, drawY, pWP, strlen(pWP));
				}

			}
		}

		SetTextAlign(hDC, TA_LEFT);
		SetTextColor(hDC, RGB(0, 0, 0));
	}

	return 0;
}

DEFINE_HOOK(46BDFA, CIsoView_DrawMouseAttachedStuff_Structure, 5)
{
	GET_STACK(const int, X, STACK_OFFS(0x94, -0x8));
	GET_STACK(const int, Y, STACK_OFFS(0x94, -0x4));

	const int nMapCoord = CMapData::Instance->GetCoordIndex(X, Y);
	const auto& cell = CMapData::Instance->CellDatas[nMapCoord];
	if (cell.Structure < 0)
		CMapData::Instance->SetStructureData(nullptr, CIsoView::CurrentObjectID(), CIsoView::CurrentHouse(), nMapCoord, "");

	return 0x46BF98;
}

DEFINE_HOOK(4676CB, CIsoView_OnLeftButtonUp_AddTube, 6)
{
	GET(CIsoViewExt*, pThis, ESI);
	GET(const int, nDestX, EDI);
	GET(const int, nDestY, EBX);

	pThis->AddTube(pThis->StartCellX, pThis->StartCellY, nDestX, nDestY);

	return 0x468548;
}

DEFINE_HOOK(4BB04C, CMapData_AddTube_IgnoreUselessNegativeOne, 5)
{
	GET(TubeData*, pTubeData, ESI);
	GET(const int, i, EBX);
	REF_STACK(ppmfc::CString, lpBuffer, STACK_OFFS(0x134, 0x124));

	enum { Continue = 0x4BB04C, Break = 0x4BB083 };

	if (pTubeData->Directions[i] == -1)
	{
		lpBuffer += ",-1";
		return Break;
	}
	else
	{
		lpBuffer += std::format(",{0:d}", pTubeData->Directions[i]).c_str();
		R->EBX(i + 1);
		return Continue;
	}
}