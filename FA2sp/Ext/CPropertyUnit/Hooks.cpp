#include <Helpers/Macro.h>

#include "Body.h"

#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(50F07C, CPropertyUnit_OnInitDialog_HidePropertyBrushCheckes, 7)
{
    GET(CPropertyUnit*, pThis, ESI);

    if (!CViewObjectsExt::InitPropertyDlgFromProperty)
    {
        for (int i = 1300; i <= 1310; ++i)
            pThis->GetDlgItem(i)->ShowWindow(SW_HIDE);
    }

    return 0;
}