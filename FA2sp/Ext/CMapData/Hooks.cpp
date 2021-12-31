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