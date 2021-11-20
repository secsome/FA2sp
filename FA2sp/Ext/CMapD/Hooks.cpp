#include <Helpers/Macro.h>

#include "../../FA2sp.h"
#include "../../Helpers/Translations.h"

DEFINE_HOOK(499659, CMapD_UpdateDialog_TheaterName, 6)
{
    GET(ppmfc::CComboBox*, pCBTheater, ECX);
    GET(const char*, lpTheaterName, EDI);

    if (strcmp(lpTheaterName, "TEMPERATE") == 0)
        pCBTheater->SetWindowText((Translations::GetTranslationItem("TheaterNameTem", FA2sp::Buffer) ? FA2sp::Buffer : "TEMPERATE"));
    else if (strcmp(lpTheaterName, "SNOW") == 0)
        pCBTheater->SetWindowText(Translations::GetTranslationItem("TheaterNameSno", FA2sp::Buffer) ? FA2sp::Buffer : "SNOW");
    else if (strcmp(lpTheaterName, "URBAN") == 0)
        pCBTheater->SetWindowText(Translations::GetTranslationItem("TheaterNameUrb", FA2sp::Buffer) ? FA2sp::Buffer : "URBAN");
    else if (strcmp(lpTheaterName, "NEWURBAN") == 0)
        pCBTheater->SetWindowText(Translations::GetTranslationItem("TheaterNameUbn", FA2sp::Buffer) ? FA2sp::Buffer : "NEWURBAN");
    else if (strcmp(lpTheaterName, "LUNAR") == 0)
        pCBTheater->SetWindowText(Translations::GetTranslationItem("TheaterNameLun", FA2sp::Buffer) ? FA2sp::Buffer : "LUNAR");
    else if (strcmp(lpTheaterName, "DESERT") == 0)
        pCBTheater->SetWindowText(Translations::GetTranslationItem("TheaterNameDes", FA2sp::Buffer) ? FA2sp::Buffer : "DESERT");
    else
        pCBTheater->SetWindowText(lpTheaterName);

    return 0x49965F;
}
