#include <CScriptTypes.h>
#include <Helpers/Macro.h>
#include <GlobalVars.h>


// Read from ScriptsRA2 in FAData
//DEFINE_HOOK(4D8020, CScriptTypes_OnInitDialog, 6)
//{
//    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
//
//    // idx begins from 0
//    constexpr int ScriptCountRA2 = 59;
//    constexpr int ScriptCountYR = 65;
//    
//    const bool& bSupportYR = *reinterpret_cast<bool*>(0x5D32AC);
//
//    const int nScriptCount = pFAData->GetInteger("ScriptsRA2", "ScriptCount", bSupportYR ? ScriptCountYR : ScriptCountRA2);
//    
//
//
//    pFAData->GetInteger("ScriptsRA2", "ScriptsCount", 64);
//    
//
//
//    return 0x4D8E06;
//}

DEFINE_HOOK(4D8D3C, test__, 7)
{
    GET(CScriptTypes*, pThis, ECX);
    HWND hwndThis = pThis->m_hWnd;
    HWND hwndTest = pThis->GetDlgItem(1919)->m_hWnd;
    Logger::Debug("this = %08X, test = %08X", hwndThis, hwndTest);
    return 0;
}