#include "Body.h"

#include <CScriptTypes.h>
#include <Helpers/Macro.h>

DEFINE_HOOK(4D8D20, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypesExt*, pThis, ECX);
    R->EAX(pThis->CScriptTypesExt::ExtOnInitDialog());
    return 0x4D8E06;
}

DEFINE_HOOK(4D6B01, CScriptTypes_OnActionUpdateParams, 7)
{
    GET(CScriptTypesExt*, pThis, ESI);
    REF_STACK(int, nActionIndex, 0x44);
    auto const pReturnAddress = pThis->CScriptTypesExt::ExtOnActionUpdateParams();
    int nCurrentActionIndex = pThis->CCBCurrentAction.GetCurSel();
    nActionIndex = pThis->CCBCurrentAction.GetItemData(nCurrentActionIndex);
    return pReturnAddress;
}

/*
* Before ini reading is done, let's use this
* hook as a temporary solution
* - secsome
*/

// TODO?