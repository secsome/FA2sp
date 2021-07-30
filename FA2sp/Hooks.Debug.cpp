#include "FA2sp.h"

#include <CINI.h>

#include <GlobalVars.h>

#include <CMapData.h>
#include <CMixFile.h>
#include <CLoading.h>
#include <CPalette.h>
#include <unordered_map>

//DEFINE_HOOK(438DB0, DebugTileDatas, 6)
//{
//    for (int i = 0; i < GlobalVars::CMapData->TileDataCount; ++i)
//    {
//        auto& tileset = GlobalVars::CMapData->TileDatas[i];
//        Logger::Debug("%d\n", tileset.Flags);
//    }
//
//    return 0x438E4E;
//}

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