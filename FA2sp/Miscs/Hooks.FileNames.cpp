#include <Helpers/Macro.h>
#include <GlobalVars.h>
#include <CINI.h>
#include <FAMemory.h>

#include <FA2PPCore.h>

#include <CLoading.h>

#include "../Logger.h"
#include "../FA2sp.h"

DEFINE_HOOK(47A3CC, FileNames_EvaIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();

    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "EVAYR", "evamd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "EVA", "eva.ini");
    
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Eva(), FALSE);
    return 0x47A3DF;
}

DEFINE_HOOK(47A342, FileNames_SoundIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "SoundYR", "soundmd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Sound", "sound.ini");

    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Sound(), FALSE);
    return 0x47A355;
}

DEFINE_HOOK(47A450, FileNames_ThemeIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "ThemeYR", "thememd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Theme", "theme.ini");

    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Theme(), FALSE);
    return 0x47A463;
}

DEFINE_HOOK(47A4D4, FileNames_AIIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "AIYR", "aimd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "AI", "ai.ini");

    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Ai(), FALSE);

    return 0x47A50C;
}

DEFINE_HOOK(479F8F, FileNames_RulesIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "RulesYR", "rulesmd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Rules", "rules.ini");

    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Rules(), FALSE);
    return 0x47A041;
}

DEFINE_HOOK(47A0C4, FileNames_ArtIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "ArtYR", "artmd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Art", "art.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Art(), FALSE);
    return 0x47A180;
}

DEFINE_HOOK(47A57D, FileNames_TemperateIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "TemperateYR", "TemperatMd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Temperate", "Temperat.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Temperate(), FALSE);
    return 0x47A5AC;
}

DEFINE_HOOK(47A61D, FileNames_SnowIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "SnowYR", "SnowMd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Snow", "Snow.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Snow(), FALSE);
    return 0x47A64C;
}

DEFINE_HOOK(47A6BD, FileNames_UrbanIni, 7)
{
    GET(CLoading*, pThis, EBP);

    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile;
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = fadata.GetString("Filenames", "UrbanYR", "UrbanMd.ini");
    }
    else
        pFile = fadata.GetString("Filenames", "Urban", "Urban.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Urban(), FALSE);
    return 0x47A6EC;
}

DEFINE_HOOK(47A76A, FileNames_UrbanNIni, 7)
{
    GET(CLoading*, pThis, EBP);
    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile = fadata.GetString("Filenames", "UrbanNYR", "UrbanNMd.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::NewUrban(), FALSE);
    return 0x47A77D;
}

DEFINE_HOOK(47A9E3, FileNames_LunarIni, 7)
{
    GET(CLoading*, pThis, EBP);
    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile = fadata.GetString("Filenames", "LunarYR", "lunarmd.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Lunar(), FALSE);
    return 0x47A9F6;
}

DEFINE_HOOK(47AA67, FileNames_DesertIni, 7)
{
    GET(CLoading*, pThis, EBP);
    INIClass& fadata = GlobalVars::INIFiles::FAData();
    CString pFile = fadata.GetString("Filenames", "DesertYR", "desertmd.ini");
    pThis->LoadTSINI(pFile, &GlobalVars::INIFiles::Desert(), FALSE);
    return 0x47AA7A;
}

DEFINE_HOOK(48768B, FileNames_MixExtension, 5)
{
    REF_STACK(CString, name, 40);
    INIClass& fadata = GlobalVars::INIFiles::FAData();
    name += fadata.GetString("Filenames", "MixExtension", "md");
    R->ECX<const char*>(name);
    return 0x487699;
}