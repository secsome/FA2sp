#include <Helpers/Macro.h>
#include <GlobalVars.h>
#include <FAMemory.h>

#include <FA2PPCore.h>

#include "../../Logger.h"
#include "../../FA2sp.h"

class FA2CMainWnd : FA2CWnd
{
public:
    void _47FFB0_loadTSINI(LPCSTR pFileName, INIClass* pINIFile, BOOL bAllowOverwrite)
    {
        JMP_THIS(0x47FFB0);
    }
};

DEFINE_HOOK(47A3CC, FileNames_EvaIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();

    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "EVAYR", "evamd.ini");
    }
    else
        pFile = pFAData->GetString("Filenames", "EVA", "eva.ini");
    
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Eva(), FALSE);
    return 0x47A3DF;
}

DEFINE_HOOK(47A342, FileNames_SoundIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "SoundYR", "soundmd.ini");
    }
    else
        pFile = pFAData->GetString("Filenames", "Sound", "sound.ini");

    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Sound(), FALSE);
    return 0x47A355;
}

DEFINE_HOOK(47A450, FileNames_ThemeIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "ThemeYR", "thememd.ini");
    }
    else
        pFile = pFAData->GetString("Filenames", "Theme", "theme.ini");

    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Theme(), FALSE);
    return 0x47A463;
}

DEFINE_HOOK(47A4D4, FileNames_AIIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "AIYR", "aimd.ini");
    }
    else
        pFile = pFAData->GetString("Filenames", "AI", "ai.ini");

    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Ai(), FALSE);

    return 0x47A50C;
}

DEFINE_HOOK(479F8F, FileNames_RulesIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "RulesYR", "rulesmd.ini");
    }
    else
        pFile = pFAData->GetString("Filenames", "Rules", "rules.ini");

    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Rules(), FALSE);

    return 0x47A041;
}

DEFINE_HOOK(47A0C4, FileNames_ArtIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->GetString("Filenames", "Art", "art.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Art(), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "ArtYR", "artmd.ini");
        pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Art(), TRUE);
    }
    return 0x47A180;
}

DEFINE_HOOK(47A57D, FileNames_TemperateIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->GetString("Filenames", "Temperate", "Temperat.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Temperate(), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "TemperateYR", "TemperatMd.ini");
        pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Temperate(), TRUE);
    }
    return 0x47A5AC;
}

DEFINE_HOOK(47A61D, FileNames_SnowIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->GetString("Filenames", "Snow", "Snow.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Snow(), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "SnowYR", "SnowMd.ini");
        pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Snow(), TRUE);
    }
    return 0x47A64C;
}

DEFINE_HOOK(47A6BD, FileNames_UrbanIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->GetString("Filenames", "Urban", "Urban.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Urban(), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->GetString("Filenames", "UrbanYR", "UrbanMd.ini");
        pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Urban(), TRUE);
    }
    return 0x47A6EC;
}

DEFINE_HOOK(47A76A, FileNames_UrbanNIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->GetString("Filenames", "UrbanNYR", "UrbanNMd.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::NewUrban(), FALSE);
    return 0x47A77D;
}

DEFINE_HOOK(47A9E3, FileNames_LunarIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->GetString("Filenames", "LunarYR", "lunarmd.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Lunar(), FALSE);
    return 0x47A9F6;
}

DEFINE_HOOK(47AA67, FileNames_DesertIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->GetString("Filenames", "DesertYR", "desertmd.ini");
    pThis->_47FFB0_loadTSINI(pFile, &GlobalVars::INIFiles::Desert(), FALSE);
    return 0x47AA7A;
}

DEFINE_HOOK(48768B, FileNames_MixExtension, 5)
{
    REF_STACK(CString, name, 40);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData();
    name += pFAData->GetString("Filenames", "MixExtension", "md");
    R->ECX<const char*>(name);
    return 0x487699;
}