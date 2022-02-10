#include <Helpers/Macro.h>

#include "../../FA2sp.h"
#include "../../Helpers/Translations.h"
#include "../../Helpers\TheaterHelpers.h"

DEFINE_HOOK(499659, CMapD_UpdateDialog_TheaterName, 6)
{
    GET(ppmfc::CComboBox*, pCBTheater, ECX);
    GET(const char*, lpTheaterName, EDI);

    pCBTheater->SetWindowText(TheaterHelpers::GetTranslatedName(lpTheaterName));

    return 0x49965F;
}
