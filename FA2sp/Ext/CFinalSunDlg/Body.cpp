#include "Body.h"

#include "../../FA2sp.h"

void CFinalSunDlgExt::ProgramStartupInit()
{
	auto addr = &CFinalSunDlgExt::PreTranslateMessageExt;
	RunTime::ResetMemoryContentAt(0x5937E8, &addr, 4);

}

BOOL CFinalSunDlgExt::PreTranslateMessageExt(MSG* pMsg)
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
            HDC  mDc = ::CreateCompatibleDC(hDC); //创建当前上下文的兼容dc(内存DC)
            HBITMAP hOldBitmap = (HBITMAP)::SelectObject(mDc, hBitmap); //将位图加载到内存DC
            ::StretchBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, mDc, 0, 0, 1920, 1080, SRCCOPY);
            ::SelectObject(mDc, hOldBitmap);
            ::DeleteObject(hBitmap);
            ::DeleteDC(mDc);
            ::EndPaint(*this, &ps);
		}
	}
	return FA2CDialog::PreTranslateMessage(pMsg);
}