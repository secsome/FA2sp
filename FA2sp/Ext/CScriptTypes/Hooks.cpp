#include <CScriptTypes.h>
#include <Helpers/Macro.h>
#include <GlobalVars.h>


// Read from ScriptsRA2 in FAData
DEFINE_HOOK(4D8020, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypes*, pThis, ECX);
    
    pThis->OnInitDialog();

    while (pThis->CCBCurrentAction.DeleteString(0) != -1)
        continue;

    constexpr int FA2ActionNamesArraySize = 59;
    const char** pFA2ActionNamesArray = reinterpret_cast<const char**>(0x5D035C);
    for (int i = 0; i < FA2ActionNamesArraySize; ++i)
        int idx = pThis->CCBCurrentAction.AddString(pFA2ActionNamesArray[i]);

    return 0x4D8E06;
}


//DEFINE_HOOK(4D6A10, CScriptTypes_OnParamConvert, 7)
//{
//    GET(CScriptTypes*, pThis, ECX);
//
//
//
//    return 0x4D7569;
//}