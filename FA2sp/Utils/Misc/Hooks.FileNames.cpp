#include <Helpers/Macro.h>
#include <GlobalVars.h>

#include <FA2PPCore.h>

#include "../../Logger.h"

class FA2CMainWnd : FA2CWnd
{
public:
    void _47FFB0_loadfiles(LPCSTR pFileName, void* pINIHeader, BOOL bAllowOverwrite)
    {
        JMP_THIS(0x47FFB0);
    }
};

class _452270_struct
{
public:
    void _452270_lockBits()
    {
        JMP_THIS(0x452270);
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
        pFile = pFAData->Read("Filenames", "EVAYR", "evamd.ini");
    }
    else
        pFile = pFAData->Read("Filenames", "EVA", "eva.ini");
    
    //&GlobalVars::INIFiles::Eva.get() - 4
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7ED848), FALSE);
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
        pFile = pFAData->Read("Filenames", "SoundYR", "soundmd.ini");
    }
    else
        pFile = pFAData->Read("Filenames", "Sound", "sound.ini");

    //&GlobalVars::INIFiles::Sound.get() - 4
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDA78), FALSE);
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
        pFile = pFAData->Read("Filenames", "ThemeYR", "thememd.ini");
    }
    else
        pFile = pFAData->Read("Filenames", "Theme", "theme.ini");

    //&GlobalVars::INIFiles::Theme.get() - 4
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7ED730), FALSE);
    return 0x47A463;
}

DEFINE_HOOK(47A4D4, FileNames_AIIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->Read("Filenames", "AI", "ai.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDB90), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->Read("Filenames", "AIYR", "aimd.ini");
        pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDB90), TRUE);
    }

    return 0x47A50C;
}

DEFINE_HOOK(479F8F, FileNames_RulesIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    //auto helper = reinterpret_cast<_452270_struct*>(0x5CC308);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->Read("Filenames", "Rules", "rules.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDDD8), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->Read("Filenames", "RulesYR", "rulesmd.ini");
        pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDDD8), TRUE);
        return 0x47A041;
        // helper->_452270_lockBits();
        // pFile = pFAData->Read("Filenames", "RulesYR", "rulesmd.ini");
        // pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(helper), TRUE);
        // return 0x479FE6;
    }
    else
        return 0x47A041;
}

DEFINE_HOOK(47A0C4, FileNames_ArtIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);

    //auto helper = reinterpret_cast<_452270_struct*>(0x5CC308);

    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile;
    pFile = pFAData->Read("Filenames", "Art", "art.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDCA8), FALSE);
    if (
        *reinterpret_cast<bool*>(0x5CE3B8) // bLoadYRFiles
        &&
        *reinterpret_cast<bool*>(0x5D32AC) // bSupportYR
        )
    {
        pFile = pFAData->Read("Filenames", "ArtYR", "artmd.ini");
        pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7EDCA8), TRUE);
        return 0x47A180;
        // helper->_452270_lockBits();
        // pFile = pFAData->Read("Filenames", "ArtYR", "artmd.ini");
        // pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(helper), TRUE);
        // return 0x47A11B;
    }
    else
        return 0x47A180;
}

#define THEATER_REPLACE_HOOK(hookname, hookaddr, retaddr, ra2key, ra2def, yrkey, yrdef, storeaddr)\
DEFINE_HOOK(hookaddr, hookname, 7)\
{\
    GET(FA2CMainWnd*, pThis, EBP);\
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();\
    CString pFile;\
    pFile = pFAData->Read("Filenames", ra2key, ra2def);\
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(storeaddr), FALSE);\
    if (\
        *reinterpret_cast<bool*>(0x5CE3B8)\
        &&\
        *reinterpret_cast<bool*>(0x5D32AC)\
        )\
    {\
        pFile = pFAData->Read("Filenames", yrkey, yrdef);\
        pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(storeaddr), TRUE);\
    }\
    return retaddr;\
}\

THEATER_REPLACE_HOOK(FileNames_TemperateIni, 47A57D, 0x47A5AC,
    "Temperate", "Temperat.ini", "TemperateYR", "TemperatMd.ini",
    0x7ED3E8);

THEATER_REPLACE_HOOK(FileNames_SnowIni, 47A61D, 0x47A64C,
    "Snow", "Snow.ini", "SnowYR", "SnowMd.ini",
    0x7ED2D0);

THEATER_REPLACE_HOOK(FileNames_UrbanIni, 47A6BD, 0x47A6EC,
    "Urban", "Urban.ini", "UrbanYR", "UrbanMd.ini",
    0x7ED1B8);

#undef THEATER_REPLACE_HOOK

DEFINE_HOOK(47A76A, FileNames_UrbanNIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->Read("Filenames", "UrbanNYR", "UrbanNMd.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7ED0A0), FALSE);
    return 0x47A77D;
}

DEFINE_HOOK(47A9E3, FileNames_LunarIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->Read("Filenames", "LunarYR", "lunarmd.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7ECF88), FALSE);
    return 0x47A9F6;
}

DEFINE_HOOK(47AA67, FileNames_DesertIni, 7)
{
    GET(FA2CMainWnd*, pThis, EBP);
    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
    CString pFile = pFAData->Read("Filenames", "DesertYR", "desertmd.ini");
    pThis->_47FFB0_loadfiles(pFile, reinterpret_cast<INIHeaderClass*>(0x7ECE70), FALSE);
    return 0x47AA7A;
}

//DEFINE_HOOK(48768B, FileNames_MixExtension, 5)
//{
//    GET(FA2CMainWnd*, pThis, EBP);
//    REF_STACK(CString, pFront, 0x2C);
//    INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
//    CString pExtension = pFAData->Read("Filenames", "MixExtension", "md");
//    pFront += pExtension;
//
//    return 0x487699;
//}