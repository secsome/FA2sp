#include "Body.h"

#include "../../FA2sp.h"

DEFINE_HOOK(4F1A40, CTileSetBrowserFrame_CreateContent, 5)
{
    GET(CTileSetBrowserFrameExt*, pThis, ECX);
    GET_STACK(LPCREATESTRUCT, lpcs, 0x4);
    GET_STACK(CCreateContext*, pContent, 0x8);

    pThis->InitTabControl();
    
    RECT rect;
    pThis->GetClientRect(&rect);
    pThis->DialogBar.FA2CDialogBar::Create(CWnd::FromHandle(CTileSetBrowserFrameExt::hTabCtrl), (LPCSTR)0xE3, 10240, 5);
    pThis->View.FA2CScrollView::Create(nullptr, nullptr, 0x50300000, &rect, CWnd::FromHandle(CTileSetBrowserFrameExt::hTabCtrl), 1, nullptr);
    pThis->RecalcLayout();
    SIZE sz{ rect.right, pThis->View.Unknown_70 };
    pThis->View.FA2CScrollView::SetScrollSizes(1, sz, (SIZE*)0x59D220, (SIZE*)0x59D220);
    R->EAX(pThis->FA2CFrameWnd::OnCreateClient(lpcs, pContent));

    return 0x4F1AF6;
}

DEFINE_HOOK(4F1B12, CTileSetBrowserFrame_RecalcLayout, 5)
{
    GET(LPRECT, lpRect, EAX);
    GET(CTileSetBrowserFrameExt*, pThis, ESI);

    RECT frameRect;
    pThis->GetClientRect(&frameRect);
    ::SetWindowPos(CTileSetBrowserFrameExt::hTabCtrl, NULL, frameRect.left, frameRect.top,
        frameRect.right - frameRect.left, frameRect.bottom - frameRect.top, SWP_NOZORDER | SWP_SHOWWINDOW);
    ::GetClientRect(CTileSetBrowserFrameExt::hTabCtrl, lpRect);

    return 0x4F1B19;
}

DEFINE_HOOK(4F1670, CTileSetBrowserFrame_ReloadComboboxes_OverlayFilter, 6)
{
    GET_STACK(int, overlayIdx, 0x24);
    GET(CComboBox*, pComboBox, EDI);
    GET(CString, name, ECX);
    if (overlayIdx <= 254) // overlay >= 255 crashes FA2, so keep it safe.
    {
        name.Format("%04d (%s)", overlayIdx, name);
        int idx = pComboBox->AddString(name);
        pComboBox->SetItemData(idx, overlayIdx);
    }
    return 0x4F1695;
}