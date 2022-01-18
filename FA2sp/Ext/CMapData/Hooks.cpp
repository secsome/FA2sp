#include "Body.h"

#include <Helpers/Macro.h>

#include "../../FA2sp.h"

DEFINE_HOOK(4C45F0, CMapData_ResizeMap, 6)
{
    if (ExtConfigs::FastResize)
    {
        LEA_STACK(MapRect* const, pRect, 0x4);

        return CMapDataExt::GetExtension()->ResizeMapExt(pRect) ? 0x4C7DC7 : 0;
    }

    return 0;
}

DEFINE_HOOK(4C3E20, CMapData_CalculateMoneyCount, 7)
{
    auto pExt = CMapDataExt::GetExtension();

    int nCount = 0;

    pExt->InitOreValue();
    for (int i = 0; i < pExt->CellDataCount; ++i)
        nCount += pExt->GetOreValueAt(pExt->CellDatas[i]);

    R->EAX(nCount);

    return 0x4C4460;
}