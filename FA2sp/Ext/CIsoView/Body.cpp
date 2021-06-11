#include "Body.h"

#include "../../FA2sp.h"

void CIsoViewExt::ProgramStartupInit()
{
    // RunTime::ResetMemoryContentAt(0x594518, CIsoViewExt::PreTranslateMessageExt);
}

BOOL CIsoViewExt::PreTranslateMessageExt(MSG* pMsg)
{
    switch (pMsg->message)
    {
    case WM_PAINT:
        if (pMsg->hwnd == *this)
        {
            PAINTSTRUCT ps;
            HDC hDC = ::BeginPaint(*this, &ps);
            RECT rect;
            ::GetClientRect(*this, &rect);
            HBITMAP hBitmap = LoadBitmap(reinterpret_cast<HINSTANCE>(FA2sp::hInstance), MAKEINTRESOURCE(23333));
            HDC  mDc = ::CreateCompatibleDC(hDC);
            HBITMAP hOldBitmap = (HBITMAP)::SelectObject(mDc, hBitmap);
            ::StretchBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, mDc, 0, 0, 1920, 1080, SRCCOPY);
            ::SelectObject(mDc, hOldBitmap);
            ::DeleteObject(hBitmap);
            ::DeleteDC(mDc);
            ::EndPaint(*this, &ps);
        }
    }
    return CIsoView::PreTranslateMessage(pMsg);
}