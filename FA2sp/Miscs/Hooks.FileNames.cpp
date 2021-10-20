#include <Helpers/Macro.h>
#include <CINI.h>
#include <FAMemory.h>

#include <FA2PPCore.h>

#include <CLoading.h>

#include "../Logger.h"
#include "../FA2sp.h"

DEFINE_HOOK(47A3CC, FileNames_EvaIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "EVAYR", "evamd.ini") :
        CINI::FAData->GetString("Filenames", "EVA", "eva.ini"),
        &CINI::Eva(), FALSE);
    
    return 0x47A3DF;
}

DEFINE_HOOK(47A342, FileNames_SoundIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "SoundYR", "soundmd.ini") :
        CINI::FAData->GetString("Filenames", "Sound", "sound.ini"),
        &CINI::Sound(), FALSE);

    return 0x47A355;
}

DEFINE_HOOK(47A450, FileNames_ThemeIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "ThemeYR", "thememd.ini") :
        CINI::FAData->GetString("Filenames", "Theme", "theme.ini"),
        &CINI::Theme(), FALSE);

    return 0x47A463;
}

DEFINE_HOOK(47A4D4, FileNames_AIIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "AIYR", "aimd.ini") :
        CINI::FAData->GetString("Filenames", "AI", "ai.ini") ,
        &CINI::Ai(), FALSE);

    return 0x47A50C;
}

DEFINE_HOOK(479F8F, FileNames_RulesIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "RulesYR", "rulesmd.ini") :
        CINI::FAData->GetString("Filenames", "Rules", "rules.ini"),
        &CINI::Rules(), FALSE);

    return 0x47A041;
}

DEFINE_HOOK(47A0C4, FileNames_ArtIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "ArtYR", "artmd.ini") :
        CINI::FAData->GetString("Filenames", "Art", "art.ini"),
        &CINI::Art(), FALSE);
    
    return 0x47A180;
}

DEFINE_HOOK(47A57D, FileNames_TemperateIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "TemperateYR", "TemperatMd.ini") :
        CINI::FAData->GetString("Filenames", "Temperate", "Temperat.ini"),
        &CINI::Temperate(), FALSE);

    return 0x47A5AC;
}

DEFINE_HOOK(47A61D, FileNames_SnowIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "SnowYR", "SnowMd.ini") :
        CINI::FAData->GetString("Filenames", "Snow", "Snow.ini"),
        &CINI::Snow(), FALSE);

    return 0x47A64C;
}

DEFINE_HOOK(47A6BD, FileNames_UrbanIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(
        CLoading::HasMdFile() ?
        CINI::FAData->GetString("Filenames", "UrbanYR", "UrbanMd.ini") :
        CINI::FAData->GetString("Filenames", "Urban", "Urban.ini"),
        &CINI::Urban(), FALSE);

    return 0x47A6EC;
}

DEFINE_HOOK(47A76A, FileNames_UrbanNIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(CINI::FAData->GetString("Filenames", "UrbanNYR", "UrbanNMd.ini"), &CINI::NewUrban(), FALSE);

    return 0x47A77D;
}

DEFINE_HOOK(47A9E3, FileNames_LunarIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(CINI::FAData->GetString("Filenames", "LunarYR", "lunarmd.ini"), &CINI::Lunar(), FALSE);

    return 0x47A9F6;
}

DEFINE_HOOK(47AA67, FileNames_DesertIni, 7)
{
    GET(CLoading*, pThis, EBP);

    pThis->LoadTSINI(CINI::FAData->GetString("Filenames", "DesertYR", "desertmd.ini"), &CINI::Desert(), FALSE);

    return 0x47AA7A;
}

DEFINE_HOOK(48768B, FileNames_MixExtension, 5)
{
    REF_STACK(ppmfc::CString, name, 40);

    name += CINI::FAData->GetString("Filenames", "MixExtension", "md");
    R->ECX<const char*>(name);

    return 0x487699;
}