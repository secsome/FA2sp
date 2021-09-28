#include <Helpers/Macro.h>

#include <MFC/ppmfc_cstring.h>
#include <CINI.h>

#include <algorithm>
#include <set>

#include "../FA2sp.h"

DEFINE_HOOK_AGAIN(4BA0A0, GetTileTypeIndex,7)
DEFINE_HOOK(4F2620, GetTileTypeIndex, 7)
{
    GET_STACK(const int, nTileSet, 0x4);
    GET_STACK(const int, nthTileInSet, 0x8);

    int nResult = 0;
    ppmfc::CString section;

    if (nthTileInSet < 100)
    {
        for (int i = 0; i < nTileSet; ++i)
        {
            section.Format("TileSet%04d", i);
            auto const nCount = CINI::CurrentTheater->GetInteger(section, "TilesInSet", -1);
            if (nCount == -1)
            {
                nResult = 0;
                break;
            }
            /*
            * I just cannot understand who did this:
            *
            * for (int j = 0; j < nCount; ++j)
            *   ++nResult;
            * 
            * WHYYYYYYYYYYYYYYY? - secsome
            */
            nResult += nCount;
        }
    }
    nResult += nthTileInSet;
    if (nResult > USHRT_MAX)
        nResult = USHRT_MAX;

    R->EAX(nResult);

    return R->Origin() + 0x4E5;
}