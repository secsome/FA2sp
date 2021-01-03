#include "Body.h"

#include <GlobalVars.h>

#include "../../FA2sp.h"

DEFINE_HOOK(4F1670, CTileSetBrowserFrame_ReloadComboboxes_OverlayFilter, 6)
{
    GET_STACK(int, overlayIdx, 0x24);
    GET(CComboBox*, pComboBox, EDI);
    GET(CString, name, ECX);
    if (overlayIdx <= 254 && ExtConfigs::OverlayFilter)
    {
        name.Format("%04d (%s)", overlayIdx, name);
        int idx = pComboBox->AddString(name);
        pComboBox->SetItemData(idx, overlayIdx);
    }
    return 0x4F1695;
}