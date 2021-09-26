#include "Body.h"

#include <FA2PP.h>

#include <CMapData.h>
#include "../../ExtraWindow/CTileManager/CTileManager.h"

#include "../../FA2sp.h"

HWND CTileSetBrowserFrameExt::hTabCtrl = NULL;

void CTileSetBrowserFrameExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597458, &CTileSetBrowserFrameExt::PreTranslateMessageExt);
}


void CTileSetBrowserFrameExt::OnBNTileManagerClicked()
{
	if (CMapData::Instance->MapWidthPlusHeight)
	{
		if (CTileManager::GetHandle() == NULL)
			CTileManager::Create(this);
		else
			::ShowWindow(CTileManager::GetHandle(), SW_SHOW);
	}
}

BOOL CTileSetBrowserFrameExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->DialogBar.GetDlgItem(6102)->GetSafeHwnd())
			this->OnBNTileManagerClicked();
	}

	return this->FA2CFrameWnd::PreTranslateMessage(pMsg);
}


void CTileSetBrowserFrameExt::InitTabControl()
{
	RECT rect;
	this->GetClientRect(&rect);

	CTileSetBrowserFrameExt::hTabCtrl = CreateWindowEx(0, WC_TABCONTROL,
		nullptr, TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE,
		rect.left + 2, rect.top + 2, rect.right - 4, rect.bottom - 4,
		*this, NULL, (HINSTANCE)FA2sp::hInstance, nullptr);
	::SendMessage(this->hTabCtrl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);
	::ShowWindow(this->hTabCtrl, SW_SHOW);

	TCITEM pitem;
	pitem.pszText = "CNM";
	TabCtrl_InsertItem(this->hTabCtrl, 0, &pitem);
}