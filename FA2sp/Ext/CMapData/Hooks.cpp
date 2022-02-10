#include "Body.h"

#include <Helpers/Macro.h>

#include "../../FA2sp.h"
#include "../../Helpers/TheaterHelpers.h"

DEFINE_HOOK(424421, CFinalSunDlg_OnInitDialog_InitOreValue, 5)
{
    CMapDataExt::GetExtension()->InitOreValue();
    return 0;
}

DEFINE_HOOK(4C3E20, CMapData_CalculateMoneyCount, 7)
{
    auto pExt = CMapDataExt::GetExtension();

    int nCount = 0;

    for (int i = 0; i < pExt->CellDataCount; ++i)
        nCount += pExt->GetOreValueAt(pExt->CellDatas[i]);

    R->EAX(nCount);

    return 0x4C4460;
}

DEFINE_HOOK(4A1DB0, CMapData_AddTiberium, 6)
{
    auto pExt = CMapDataExt::GetExtension();

    GET_STACK(unsigned char, nOverlay, 0x4);
    GET_STACK(unsigned char, nOverlayData, 0x8);
    
    pExt->MoneyCount += CMapDataExt::GetExtension()->GetOreValue(nOverlay, nOverlayData);

    return 0x4A238E;
}

DEFINE_HOOK(4A17C0, CMapData_DeleteTiberium, 6)
{
    auto pExt = CMapDataExt::GetExtension();

    GET_STACK(unsigned char, nOverlay, 0x4);
    GET_STACK(unsigned char, nOverlayData, 0x8);

    pExt->MoneyCount -= CMapDataExt::GetExtension()->GetOreValue(nOverlay, nOverlayData);

    return 0x4A1D9E;
}

DEFINE_HOOK(4BB04A, CMapData_AddTube_IgnoreUselessNegativeOne, 7)
{
    GET(TubeData*, pTubeData, ESI);
    REF_STACK(ppmfc::CString, lpBuffer, STACK_OFFS(0x134, 0x124));

    for (int i = 0; i < 100; ++i)
    {
        if (pTubeData->Directions[i] == -1)
        {
            lpBuffer += ",-1";
            break;
        }

        lpBuffer += ',';
        lpBuffer += pTubeData->Directions[i] + '0';
    }

    return 0x4BB083;
}

DEFINE_HOOK(47AB50, CLoading_InitPics_InitOverlayTypeDatas, 7)
{
    CMapDataExt::OverlayTypeDatas.clear();

    for (const auto& id : Variables::Rules.ParseIndicies("OverlayTypes", true))
    {
        auto& item = CMapDataExt::OverlayTypeDatas.emplace_back();
        item.Rock = Variables::Rules.GetBool(id, "IsARock");
    }

    return 0;
}


DEFINE_HOOK(49DFB4, CMapData_LoadMap_InvalidTheater, 6)
{
    GET(char*, theaterName, EDI);

    for (auto& str : TheaterHelpers::GetEnabledTheaterNames()) 
    {
        if (strcmp(str, theaterName) == 0)
            return 0;
    }

    return 0x49EDD9;
}