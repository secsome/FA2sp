#include "Body.h"

#include <CScriptTypes.h>
#include <Helpers/Macro.h>

DEFINE_HOOK(4D8D20, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypesExt*, pThis, ECX);
    R->EAX(pThis->CScriptTypesExt::ExtOnInitDialog());
    return 0x4D8E06;
}


DEFINE_HOOK(4D6A10, CScriptTypes_OnActionUpdateParams, 7)
{
    GET(CScriptTypesExt*, pThis, ECX);
    return pThis->CScriptTypesExt::ExtOnActionUpdateParams();
}