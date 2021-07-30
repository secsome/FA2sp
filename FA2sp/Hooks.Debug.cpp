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