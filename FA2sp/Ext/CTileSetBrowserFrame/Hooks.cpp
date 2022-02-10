#include "Body.h"

#include "../../FA2sp.h"

#include "TabPages/TriggerSort.h"

#include "../../Helpers/Translations.h"

DEFINE_HOOK(4F1A40, CTileSetBrowserFrame_CreateContent, 5)
{
    GET(CTileSetBrowserFrameExt*, pThis, ECX);
    GET_STACK(LPCREATESTRUCT, lpcs, 0x4);
    GET_STACK(ppmfc::CCreateContext*, pContent, 0x8);

    pThis->InitTabControl();
    
    auto const pTab = ppmfc::CWnd::FromHandle(CTileSetBrowserFrameExt::hTabCtrl);

    RECT rect;
    pThis->GetClientRect(&rect);
    pThis->DialogBar.Create(pTab, MAKEINTRESOURCE(0xE3), 0x2800, 5);

    Translations::TranslateItem(&pThis->DialogBar, 6102, "DialogBar.TileManager");
    Translations::TranslateItem(&pThis->DialogBar, 1368, "DialogBar.TerrainOrGround");
    Translations::TranslateItem(&pThis->DialogBar, 1369, "DialogBar.OverlayAndSpecial");

    pThis->View.Create(nullptr, nullptr, 0x50300000, rect, pTab, 1, nullptr);
    pThis->ppmfc::CFrameWnd::RecalcLayout();
    SIZE sz{ rect.right, pThis->View.ScrollWidth };
    pThis->View.SetScrollSizes(1, sz);
    R->EAX(pThis->ppmfc::CFrameWnd::OnCreateClient(lpcs, pContent));

    return 0x4F1AF6;
}

DEFINE_HOOK(4F1B00, CTileSetBrowserFrame_RecalcLayout, 7)
{
    GET(CTileSetBrowserFrameExt*, pThis, ECX);

    RECT frameRect, tabRect;
    pThis->GetClientRect(&frameRect);
    ::MoveWindow(CTileSetBrowserFrameExt::hTabCtrl, 0, 0, frameRect.right - frameRect.left,
        frameRect.bottom - frameRect.top, TRUE);

    ::GetClientRect(CTileSetBrowserFrameExt::hTabCtrl, &tabRect);

    pThis->DialogBar.MoveWindow(2, 29, tabRect.right - tabRect.left - 6, 110, FALSE);
    pThis->View.MoveWindow(2, 139, tabRect.right - tabRect.left - 6, tabRect.bottom - 145, FALSE);

    SIZE sz{ tabRect.right,pThis->View.ScrollWidth };
    pThis->View.SetScrollSizes(1, sz);

    TriggerSort::Instance.OnSize();

    return 0x4F1B8A;
}

DEFINE_HOOK(4F1670, CTileSetBrowserFrame_ReloadComboboxes_OverlayFilter, 6)
{
    GET_STACK(int, overlayIdx, 0x24);
    GET(ppmfc::CComboBox*, pComboBox, EDI);
    GET(ppmfc::CString, name, ECX);
    if (overlayIdx < 255) // overlay >= 255 crashes FA2, so keep it safe.
    {
        name.Format("%04d (%s)", overlayIdx, name);
        int idx = pComboBox->AddString(name);
        pComboBox->SetItemData(idx, overlayIdx);
    }
    return 0x4F1695;
}