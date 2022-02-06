#include <Helpers/Macro.h>
#include <CCreateMap3A.h>
#include <CLoading.h>

#include "../../FA2sp.h"
#include "../../Helpers/Translations.h"
#include "../../Helpers/TheaterHelpers.h"

DEFINE_HOOK(4D2E80, CCreateMap3A_OnInitDialog, 5)
{
    GET(CCreateMap3A*, pThis, ECX);

    pThis->ppmfc::CDialog::OnInitDialog();
    auto pCBTheater = (ppmfc::CComboBox*)pThis->GetDlgItem(1046);

    for (auto& str : TheaterHelpers::GetEnabledTheaterNames())
    {
        pCBTheater->AddString(TheaterHelpers::GetTranslatedName(str));
    }

    pThis->TheaterIndex = 0;
    pThis->DefaultHeight = 0;
    pThis->MapWidth = pThis->MapHeight = 80;

    pThis->ppmfc::CDialog::UpdateData(false);

    R->AL(true);

    return 0x4D2F3D;
}

DEFINE_HOOK(4D2F40, CCreateMap3A_OnOK, 5)
{
    GET(CCreateMap3A*, pThis, ECX);

    pThis->UpdateData();

    if (pThis->MapWidth > 256 || pThis->MapWidth < 1 || pThis->MapHeight > 256 || pThis->MapHeight < 1)
        ::MessageBox(NULL, "Width and Height must both be between 1 and 256.", "Error", MB_OK);
    else
        pThis->ppmfc::CDialog::OnOK();

    return 0x4D2FA7;
}