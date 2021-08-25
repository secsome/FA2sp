#include <CMapData.h>
#include <CINI.h>
#include <CFinalSunDlg.h>
#include <CIsoView.h>
#include <CMixFile.h>
#include <CLoading.h>
#include <CPalette.h>
#include <unordered_map>
#include <Drawing.h>

#include <GlobalVars.h>

#include "FA2sp.h"
 
//DEFINE_HOOK(438DB0, DebugDrawDataMap, 6)
//{
//    Screenshot("CurrentSurface.bmp", GlobalVars::Dialogs::CFinalSunDlg->MyViewFrame.pIsoView->lpDDPrimarySurface);
//
//    ImageDataMap& tmp = *reinterpret_cast<ImageDataMap*>(0x72CBC8);
//
//    SomeDataMap& tmp2 = *reinterpret_cast<SomeDataMap*>(0x72A870);
//    for (auto& x : tmp2)
//    {
//        Logger::Debug("%s %d\n", x.first, x.second);
//    }
//
//    for (auto& pair : tmp)
//    {
//        ImageDataClass& value = pair.second;
//
//        if (pair.first.IsEmpty())
//            continue;
//
//        if (value.Flag == ImageDataFlag::SurfaceData)
//        {
//            if (value.lpSurface)
//            {
//                // Screenshot("Exports\\" + pair.first + ".bmp", value.lpSurface);
//            }
//
//        }
//        else
//        {
//            if (pair.second.FullHeight == 0 || pair.second.FullWidth == 0)
//                continue;
//
//            bitmap_image bmp;
//            bmp.setwidth_height(value.FullWidth, value.FullHeight, true);
//
//            int count = 0;
//            for (int j = 0; j < bmp.height(); ++j)
//            {
//                for (int i = 0; i < bmp.width(); ++i)
//                {
//                    bmp.set_pixel(i, j, value.pPalette->GetByteColor(value.pImageBuffer[count]));
//                    ++count;
//                }
//            }
//
//            bmp.save_image((const char*)("Exports2\\" + pair.first + ".bmp"));
//        }
//    }
//
//    return 0x438E4E;
//}
 
//
//DEFINE_HOOK(4B2610, CMapData_QueryUIName_Debug, 7)
//{
//    /*GET_STACK(const char*, pRegName, 0x4);
//    Logger::Debug(__FUNCTION__" pRegName = %s\n", pRegName);
//    return 0;*/
//
//    static bool asd = true;
//    if (asd)
//    {
//        auto& ini = GlobalVars::INIFiles::CurrentDocument();
//        for (auto& x : ini.Dict)
//        {
//            if (auto name = ini.TryGetString(x.first, "Name"))
//                Logger::Debug("%s %s\n", x.first, name);
//        }
//        asd = false;
//    }
//
//    return 0;
//}

//DEFINE_HOOK(438DB0, DebugTileDatas, 6)
//{
//    auto& tileset = GlobalVars::CMapData->CellDatas[GlobalVars::CMapData->GetCoordIndex(50, 50)];
//    Logger::Debug("%d\n", tileset.LAT);
//
//    return 0x438E4E;
//}
//
//DEFINE_HOOK(45AF76, CIsoView_OnMouseMove_DebugCurrentCellData, 5)
//{
//    GET(int, Y, EDI);
//    GET(int, X, EBX);
//
//    auto& cell = GlobalVars::CMapData->CellDatas[GlobalVars::CMapData->GetCoordIndex(X, Y)];
//
//    ppmfc::CString buffer;
//    char format[] =
//        "[%d, %d]\n"
//        "Unit = %d  "
//        "Infantry = {%d, %d, %d}\n"
//        "Aircraft = %d  "
//        "Structure = %d\n"
//        "TypeListIndex = %d\n"
//        "TerrainType = %d\n"
//        "Smudge = %d\n"
//        "SmudgeType = %d\n"
//        "Waypoint = %d\n"
//        "BaseNode = {%d, %d, %s}\n"
//        "Overlay = {%d, %d}\n"
//        "TileIndex = %d  "
//        "Short_30 = %d  "
//        "TileSubIndex = %d   "
//        "Height = %d    "
//        "IceGrowth = %d\n"
//        "CellTag = %d   "
//        "Tube = %d  "
//        "TubeDir = %d\n"
//        "StatusFlag = %d    "
//        "LAT = %d";
//
//    buffer.Format(format,
//        X, Y,
//        cell.Unit, cell.Infantry[0], cell.Infantry[1], cell.Infantry[2],
//        cell.Aircraft, cell.Structure,
//        cell.TypeListIndex,
//        cell.TerrainType,
//        cell.Smudge,
//        cell.SmudgeType,
//        cell.Waypoint,
//        cell.BaseNode.BuildingID, cell.BaseNode.BasenodeID, cell.BaseNode.House,
//        cell.Overlay, cell.OverlayData,
//        cell.TileIndex, cell.Short_30, cell.TileSubIndex, cell.Height, cell.IceGrowth,
//        cell.CellTag, cell.Tube, cell.TubeDir,
//        cell.StatusFlag, cell.LAT);
//
//    auto pDC = GlobalVars::Dialogs::CFinalSunDlg->MyViewFrame.pIsoView->GetDC();
//    RECT rect{ 0,35,0,0 };
//    pDC->SetBkMode(OPAQUE);
//    pDC->DrawText((LPCSTR)buffer, &rect, DT_CALCRECT);
//    pDC->DrawText((LPCSTR)buffer, &rect, NULL);
//
//    return 0;
//}

//DEFINE_HOOK(45AF76, CIsoView_OnMouseMove_DebugCurrentCellData, 5)
//{
//    struct TheaterRelatedData
//    {
//        int Unknown_0;
//        char* Pointer_4;
//        __int16 SubTileCount;
//        __int16 Short_A;
//        int Unknown_C;
//        int Unknown_10;
//        int Unknown_14;
//        int Unknown_18;
//        int Unknown_1C;
//        int Unknown_20;
//        int Unknown_24;
//        int Unknown_28;
//        int Unknown_2C;
//        int Unknown_30;
//        int Unknown_34;
//        TheaterRelatedData* Next_38;
//        unsigned __int8 Byte_3C;
//        unsigned __int8 Byte_3D;
//        unsigned __int8 Byte_3E;
//        unsigned __int8 Byte_3F;
//    };
//
//    GET(int, Y, EDI);
//    GET(int, X, EBX);
//
//    auto& cell = GlobalVars::CMapData->CellDatas[GlobalVars::CMapData->GetCoordIndex(X, Y)];
//    auto& data = (*(TheaterRelatedData**)0x7EE070)[cell.TileIndex];
//    int dwTileIndexCount = *(short*)(0x7EE074);
//
//    ppmfc::CString buffer;
//
//    char format[] =
//        "[%d, %d]\n"
//        "TileIndex = %d  "
//        "TileSubIndex = %d   "
//        "Height = %d\n"
//        "SubTileCount = %d  TileIndexCount = %d";
//
//    buffer.Format(format,
//        X, Y,
//        cell.TileIndex,
//        cell.TileSubIndex,
//        cell.Height,
//        data.SubTileCount,
//        dwTileIndexCount);
//
//    auto pDC = GlobalVars::Dialogs::CFinalSunDlg->MyViewFrame.pIsoView->GetDC();
//    RECT rect{ 0,35,0,0 };
//    pDC->SetBkMode(OPAQUE);
//    pDC->DrawText((LPCSTR)buffer, &rect, DT_CALCRECT);
//    pDC->DrawText((LPCSTR)buffer, &rect, NULL);
//
//    return 0;
//}
