#include <Helpers/Macro.h>

#include "Body.h"

#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(401561, CPropertyAircraft_OnInitDialog_HidePropertyBrushCheckes, 7)
{
    GET(CPropertyAircraft*, pThis, ESI);

    if (!ObjectBrowserControlExt::InitPropertyDlgFromProperty)
    {
        for (int i = 1300; i <= 1308; ++i)
            pThis->GetDlgItem(i)->ShowWindow(SW_HIDE);
    }

    return 0;
}