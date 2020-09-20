#include <CTileSetBrowserView.h>
#include <Helpers/Macro.h>
#include <GlobalVars.h>

#include <FA2PP.h>

#include "../../FA2sp.h"

DEFINE_HOOK(4F1670, CTileSetBrowserView_ReloadComboboxes, 6)
{
    CTreeView

    INIClass* pRules = &GlobalVars::INIFiles::Rules.get();

    GET_STACK(int, overlayIdx, 0x24);

    //if (ExtConfigs::OverlayFilter) {
    if (1) {
        char buf[8];
        _itoa_s(overlayIdx, buf, 10);
        auto const& pOvlName = pRules->GetString("OverlayTypes", buf);

        if (!pRules->GetBool(pOvlName, "Wall.HasConnection", true))
            return 0x4F1695;
    }

    GET(CString, name, ECX);
    name.Format("%04d (%s)", overlayIdx, name);
    R->ECX<const char*>(name);
    return 0;
}