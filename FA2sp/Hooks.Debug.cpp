#include "FA2sp.h"

#include <CINI.h>

#include <GlobalVars.h>

#include <CMapData.h>
#include <CFinalSunDlg.h>
#include <CIsoView.h>
#include <CMixFile.h>
#include <CLoading.h>
#include <CPalette.h>
#include <unordered_map>

//DEFINE_HOOK(438DB0, DebugTileDatas, 6)
//{
//    auto& tileset = GlobalVars::CMapData->CellDatas[GlobalVars::CMapData->GetCoordIndex(50, 50)];
//    Logger::Debug("%d\n", tileset.LAT);
//
//    return 0x438E4E;
//}
//
DEFINE_HOOK(45AF76, CIsoView_OnMouseMove_DebugCurrentCellData, 5)
{
    GET(int, Y, EDI);
    GET(int, X, EBX);

    auto& cell = GlobalVars::CMapData->CellDatas[GlobalVars::CMapData->GetCoordIndex(X, Y)];

    ppmfc::CString buffer;
    char format[] =
        "[%d, %d]\n"
        "Unit = %d  "
        "Infantry = {%d, %d, %d}\n"
        "Aircraft = %d  "
        "Structure = %d\n"
        "TypeListIndex = %d\n"
        "TerrainType = %d\n"
        "Smudge = %d\n"
        "SmudgeType = %d\n"
        "Waypoint = %d\n"
        "BaseNode = {%d, %d, %s}\n"
        "Overlay = {%d, %d}\n"
        "TileIndex = %d  "
        "Short_30 = %d  "
        "TileSubIndex = %d   "
        "Height = %d    "
        "IceGrowth = %d\n"
        "CellTag = %d   "
        "Tube = %d  "
        "TubeDir = %d\n"
        "StatusFlag = %d    "
        "LAT = %d";

    buffer.Format(format,
        X, Y,
        cell.Unit, cell.Infantry[0], cell.Infantry[1], cell.Infantry[2],
        cell.Aircraft, cell.Structure,
        cell.TypeListIndex,
        cell.TerrainType,
        cell.Smudge,
        cell.SmudgeType,
        cell.Waypoint,
        cell.BaseNode.BuildingID, cell.BaseNode.BasenodeID, cell.BaseNode.House,
        cell.Overlay, cell.OverlayData,
        cell.TileIndex, cell.Short_30, cell.TileSubIndex, cell.Height, cell.IceGrowth,
        cell.CellTag, cell.Tube, cell.TubeDir,
        cell.StatusFlag, cell.LAT);

    auto pDC = GlobalVars::Dialogs::CFinalSunDlg->MyViewFrame.pIsoView->GetDC();
    RECT rect{ 0,35,0,0 };
    pDC->SetBkMode(OPAQUE);
    pDC->DrawText((LPCSTR)buffer, &rect, DT_CALCRECT);
    pDC->DrawText((LPCSTR)buffer, &rect, NULL);

    return 0;
}

//DEFINE_HOOK(438DB0, DebugNames, 6)
//{
//    using CSFMap = FAMap<ppmfc::CString, const wchar_t*, 0x5D8CE4, 0>;
//    CSFMap& data = *reinterpret_cast<CSFMap*>(0x5E7C88);
//
//    for (auto& pair : data)
//    {
//        ppmfc::CString str = CMapData::GetUIName(pair.first);
//        // ppmfc::CString str(pair.second);
//        Logger::Debug("[%s] %s\n", pair.first, str);
//    }
//
//    return 0x438E4E;
//}