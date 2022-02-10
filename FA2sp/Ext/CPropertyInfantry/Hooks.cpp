#include <Helpers/Macro.h>

#include "Body.h"

#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(451AEC, CPropertyInfantry_OnInitDialog_HidePropertyBrushCheckes, 7)
{
    GET(CPropertyInfantry*, pThis, ESI);

    if (!CViewObjectsExt::InitPropertyDlgFromProperty)
    {
        for (int i = 1300; i <= 1309; ++i)
            pThis->GetDlgItem(i)->ShowWindow(SW_HIDE);
    }

    return 0;
}