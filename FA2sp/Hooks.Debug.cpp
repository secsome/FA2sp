#ifdef _DEBUG

#include <CMapData.h>
#include <CFinalSunDlg.h>
#include <CIsoView.h>
#include <CPalette.h>
#include <Drawing.h>
#include <CTileTypeClass.h>

#include "Logger.h"

//DEFINE_HOOK(49C2B8, CMapData_UpdateINIFile_LoadFromINI, 7)
//{
//    CMapData::Instance->UpdateSize();
//    CMapData::Instance->InitMinimap();
//
//    CMapData::Instance->SlopeSetPieces = CINI::CurrentTheater->GetInteger("General", "SlopeSetPieces");
//    CMapData::Instance->RampBase = CINI::CurrentTheater->GetInteger("General", "RampBase");
//    CMapData::Instance->RampSmooth = CINI::CurrentTheater->GetInteger("General", "RampSmooth");
//    CMapData::Instance->CliffSet = CINI::CurrentTheater->GetInteger("General", "CliffSet");
//    CMapData::Instance->WaterSet = CINI::CurrentTheater->GetInteger("General", "WaterSet");
//    CMapData::Instance->ShorePieces = CINI::CurrentTheater->GetInteger("General", "ShorePieces");
//    CMapData::Instance->RampBase = CINI::CurrentTheater->GetInteger("General", "RampBase");
//    CMapData::Instance->Ramps2 = CINI::CurrentTheater->GetInteger("NewUrbanInfo", "Ramps2");
//    CMapData::Instance->Morphable2= CINI::CurrentTheater->GetInteger("NewUrbanInfo", "Morphable2");
//    CMapData::Instance->Cliff2 = CINI::CurrentTheater->GetInteger("NewUrbanInfo", "Cliffs2");
//    CMapData::Instance->CliffWaters2= CINI::CurrentTheater->GetInteger("NewUrbanInfo", "CliffsWaters");
//
//    CMapData::Instance->CliffSetCount = CTileTypeClass::GetTileIndex(CMapData::Instance->CliffSet, 0);
//    CMapData::Instance->RampBaseCount = CTileTypeClass::GetTileIndex(CMapData::Instance->RampBase, 0);
//    CMapData::Instance->Ramps2Count = CTileTypeClass::GetTileIndex(CMapData::Instance->Ramps2, 0);
//    CMapData::Instance->Morphable2Count = CTileTypeClass::GetTileIndex(CMapData::Instance->Morphable2, 0);
//    CMapData::Instance->Cliffs2Count = CTileTypeClass::GetTileIndex(CMapData::Instance->Cliff2, 0);
//    
//
//    CMapData::Instance->TypesInit_4AD930();
//    CMapData::Instance->InitializeBuildingTypes(nullptr);
//    CMapData::Instance->InitializeTerrainTypes(nullptr);
//    CMapData::Instance->InitializeSmudges(nullptr);
//    CMapData::Instance->UpdateMapFieldData_Field(false);
//    CMapData::Instance->UpdateMapFieldData_Aircraft(false);
//
//    R->EBP(R->Stack32(STACK_OFFS(0x110, 0x74)));
//
//    return 0x49D121;
//}

//DEFINE_HOOK(4B9C39, CMapData_UpdateIniFile_Debug, 5)
//{
//    return 0;
//}

//
//DEFINE_HOOK(438DB0, CrashMePlease, 6)
//{
//    return 0x114514;
//}

//DEFINE_HOOK(45AF76, CIsoView_OnMouseMove_DebugCurrentCellData, 5)
//{
//    GET(int, Y, EDI);
//    GET(int, X, EBX);
//
//    auto& cell = CMapData::Instance->CellDatas[CMapData::Instance->GetCoordIndex(X, Y)];
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
//        cell.CellTag, cell.Tube, cell.TubeDataIndex,
//        cell.StatusFlag, cell.LAT);
//
//    auto pDC = CFinalSunDlg::Instance->MyViewFrame.pIsoView->GetDC();
//    RECT rect{ 0,35,0,0 };
//    pDC->SetBkMode(OPAQUE);
//    pDC->DrawText((LPCSTR)buffer, &rect, DT_CALCRECT);
//    pDC->DrawText((LPCSTR)buffer, &rect, NULL);
//
//    return 0;
//}
//
//DEFINE_HOOK(438DB0, DebugTilesetDatas, 6)
//{
//    struct TileBlockData
//    {
//        int Unknown_0;
//        ImageDataClass* NormalImage;
//        void* Pointer_8;
//        int Unknown_C;
//        int Unknown_10;
//        unsigned char Height;
//        unsigned char Byte_15;
//        unsigned char Byte_16;
//        unsigned char ColorLeft_Red;
//        unsigned char ColorLeft_Green;
//        unsigned char ColorLeft_Blue;
//        unsigned char ColorRight_Red;
//        unsigned char ColorRight_Green;
//        unsigned char ColorRight_Blue;
//        unsigned char Byte_1D;
//        unsigned char Byte_1E;
//        unsigned char Byte_1F;
//    };
//
//    struct TheaterRelatedData
//    {
//        int TileSet;
//        TileBlockData* SubTileDatas;
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
//    Logger::Raw(__FUNCTION__" Runs.\n");
//    auto datas = *(TheaterRelatedData**)0x7EE070;
//    int dwTileIndexCount = ((unsigned short*)0x7EE074)[1];
//
//    Logger::Raw("count = %d\n", dwTileIndexCount);
//
//    for (int i = 0; i < dwTileIndexCount; ++i)
//    {
//        auto& pData = datas[i];
//        Logger::Raw("\n\n===Tileset = %d(%d)===\n", pData.TileSet, i);
//        for (int j = 0; j < pData.SubTileCount; ++j)
//        {
//            auto& pSubData = pData.SubTileDatas[j];
//            Logger::Raw("   ---Subtile = %d---\n", j);
//            Logger::Raw("   0x0 = %d, 0x4 = %p, 0x8 = %p, 0xC = %d, 0x10 = %d\n",
//                pSubData.Unknown_0, pSubData.NormalImage, pSubData.Pointer_8, pSubData.Unknown_C, pSubData.Unknown_10);
//            Logger::Raw("   Height = %d, 0x15 = %d, 0x16 = %d\n", pSubData.Height, pSubData.Byte_15, pSubData.Byte_16);
//            Logger::Raw("   Left Color = (%d %d %d), Right Color = (%d %d %d)\n",
//                pSubData.ColorLeft_Red, pSubData.ColorLeft_Green, pSubData.ColorLeft_Blue,
//                pSubData.ColorRight_Red, pSubData.ColorRight_Green, pSubData.ColorRight_Blue);
//            Logger::Raw("   0x1D = %d, 0x1E = %d, 0x1F = %d\n", pSubData.Byte_1D, pSubData.Byte_1E, pSubData.Byte_1F);
//        }
//        Logger::Raw("0xA = %d\n", pData.Short_A);
//        Logger::Raw("0xC = %d, 0x10 = %d, 0x14 = %d, 0x18 = %d\n", pData.Unknown_C, pData.Unknown_10, pData.Unknown_14, pData.Unknown_18);
//        Logger::Raw("0x1C = %d, 0x20 = %d, 0x24 = %d, 0x28 = %d\n", pData.Unknown_1C, pData.Unknown_20, pData.Unknown_24, pData.Unknown_28);
//        Logger::Raw("0x2C = %d, 0x30 = %d, 0x34 = %d, 0x38 = %p\n", pData.Unknown_2C, pData.Unknown_30, pData.Unknown_34, pData.Next_38);
//        Logger::Raw("0x3C = %d, 0x3D = %d, 0x3E = %d, 0x3F = %d\n", pData.Byte_3C, pData.Byte_3D, pData.Byte_3E, pData.Byte_3F);
//    }
//
//    return 0x438E4E;
//}

#endif