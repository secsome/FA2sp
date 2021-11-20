#include <Helpers/Macro.h>
#include <CCreateMap3A.h>
#include <CLoading.h>

#include "../../FA2sp.h"
#include "../../Helpers/Translations.h"

DEFINE_HOOK(4D2E80, CCreateMap3A_OnInitDialog, 5)
{
    GET(CCreateMap3A*, pThis, ECX);

    pThis->FA2CDialog::OnInitDialog();
    auto pCBTheater = (ppmfc::CComboBox*)pThis->GetDlgItem(1046);
    pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameTem", FA2sp::Buffer) ? FA2sp::Buffer : "TEMPERATE");
    pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameSno", FA2sp::Buffer) ? FA2sp::Buffer : "SNOW");
    pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameUrb", FA2sp::Buffer) ? FA2sp::Buffer : "URBAN");
    if (CLoading::HasMdFile)
    {
        pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameUbn", FA2sp::Buffer) ? FA2sp::Buffer : "NEWURBAN");
        pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameLun", FA2sp::Buffer) ? FA2sp::Buffer : "LUNAR");
        pCBTheater->AddString(Translations::GetTranslationItem("TheaterNameDes", FA2sp::Buffer) ? FA2sp::Buffer : "DESERT");
    }
    pThis->TheaterIndex = 0;
    pThis->DefaultHeight = 0;
    pThis->MapWidth = pThis->MapHeight = 80;

    pThis->FA2CDialog::UpdateData(false);

    R->AL(true);

    return 0x4D2F3D;
}