#include "Body.h"

#include <CScriptTypes.h>
#include <Helpers/Macro.h>

#include <vector>

DEFINE_HOOK(4D8D20, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypesExt*, pThis, ECX);
    R->EAX(pThis->CScriptTypesExt::OnInitDialog());
    return 0x4D8E06;
}


//DEFINE_HOOK(4D6A10, CScriptTypes_OnActionUpdateParams, 7)
//{
//    GET(CScriptTypes*, pThis, ECX);
//
//
//
//    return 0x4D7569;
//}