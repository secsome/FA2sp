#include "CObjectSearch.h"

#include <FA2PP.h>
#include <Helpers/Macro.h>

#include "../../FA2sp.h"

DEFINE_HOOK(438DB0, CFinalSunDlg_MapTools_SearchWaypoint_ReplaceToCObjectSearch, 6)
{
    if (ExtConfigs::EnableSearch)
    {
        if (GlobalVars::CurrentMapWidthPlusHeight())
        {
            GET(CFinalSunDlg*, pDlg, ECX);

            if (CObjectSearch::GetHandle() == NULL)
                CObjectSearch::Create(pDlg);
            else
                ::ShowWindow(CObjectSearch::GetHandle(), SW_SHOW);
        }
        return 0x438E4E;
    }
    return 0;
}