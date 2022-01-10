#include "Body.h"

#include <Helpers/Macro.h>

DEFINE_HOOK(41FAD0, CFinalSunApp_InitInstance, 8)
{
    R->EAX(CFinalSunAppExt::GetInstance()->InitInstanceExt());

    return 0x422052;
}