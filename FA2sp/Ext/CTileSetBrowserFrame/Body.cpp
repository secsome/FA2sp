#include "Body.h"

#include <FA2PP.h>

#include <CMapData.h>
#include "../../ExtraWindow/CTileManager/CTileManager.h"

#include "../../FA2sp.h"

HWND CTileSetBrowserFrameExt::hTabCtrl = NULL;
HIMAGELIST CTileSetBrowserFrameExt::hTabImageList = NULL;

void CTileSetBrowserFrameExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597458, &CTileSetBrowserFrameExt::PreTranslateMessageExt);
	RunTime::ResetMemoryContentAt(0x597444, &CTileSetBrowserFrameExt::OnNotifyExt);
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

BOOL CTileSetBrowserFrameExt::OnNotifyExt(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR lpNmhdr = reinterpret_cast<LPNMHDR>(lParam);
	if (lpNmhdr->hwndFrom == this->hTabCtrl)
	{
		switch (lpNmhdr->code)
		{
		case TCN_SELCHANGE:
			switch (static_cast<TabPage>(TabCtrl_GetCurSel(this->hTabCtrl)))
			{
			default:
			case TabPage::TilesetBrowser:
				this->DialogBar.ShowWindow(SW_SHOW);
				this->View.ShowWindow(SW_SHOW);
				break;
			case TabPage::TriggerSort:
				this->DialogBar.ShowWindow(SW_HIDE);
				this->View.ShowWindow(SW_HIDE);
				break;
			}
			return TRUE;
		default:
			break;
		}
	}
	return this->FA2CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CTileSetBrowserFrameExt::InitTabControl()
{
	RECT rect;
	this->GetClientRect(&rect);

	this->hTabCtrl = CreateWindowEx(0, WC_TABCONTROL,
		nullptr, TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE,
		rect.left + 2, rect.top + 2, rect.right - 4, rect.bottom - 4,
		*this, NULL, (HINSTANCE)FA2sp::hInstance, nullptr);
	::SendMessage(this->hTabCtrl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);
	::ShowWindow(this->hTabCtrl, SW_SHOW);
	
	::SetWindowPos(this->hTabCtrl, *this, NULL, NULL, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

	this->hTabImageList = ImageList_Create(32, 32, ILC_COLOR24, 0, 1);

	TCITEM pitem;
	pitem.mask = TCIF_TEXT | TCIF_IMAGE;
	pitem.iImage = -1;

	pitem.pszText = "Tile placement";
	TabCtrl_InsertItem(this->hTabCtrl, 0, &pitem);
	pitem.pszText = "Trigger sort";
	TabCtrl_InsertItem(this->hTabCtrl, 1, &pitem);
}