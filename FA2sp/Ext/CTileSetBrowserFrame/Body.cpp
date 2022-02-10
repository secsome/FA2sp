#include "Body.h"

#include <FA2PP.h>

#include <CMapData.h>
#include <CFinalSunDlg.h>
#include "../../ExtraWindow/CTileManager/CTileManager.h"

#include "../../FA2sp.h"
#include "../CTriggerFrame/Body.h"

#include "TabPages/TriggerSort.h"

#include "../../Helpers/Translations.h"

HWND CTileSetBrowserFrameExt::hTabCtrl = NULL;

void CTileSetBrowserFrameExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597458, &CTileSetBrowserFrameExt::PreTranslateMessageExt);
	RunTime::ResetMemoryContentAt(0x597444, &CTileSetBrowserFrameExt::OnNotifyExt);
	RunTime::ResetMemoryContentAt(0x597440, &CTileSetBrowserFrameExt::OnCommandExt);
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
	if (pMsg->message == WM_COMMAND)
	{
		auto nID = LOWORD(pMsg->wParam);
		auto nHi = HIWORD(pMsg->wParam);

		if (nID == (UINT)TriggerSort::MenuItem::AddTrigger)
		{
			if (CFinalSunDlg::Instance->TriggerFrame.m_hWnd)
			{
				CTriggerFrameExt::CreateFromTriggerSort = true;
				TriggerSort::Instance.Menu_AddTrigger();
				CFinalSunDlg::Instance->TriggerFrame.OnBNNewTriggerClicked();
				CTriggerFrameExt::CreateFromTriggerSort = false;
			}

			return TRUE;
		}
	}
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->DialogBar.GetDlgItem(6102)->GetSafeHwnd())
			this->OnBNTileManagerClicked();
	}
	if (pMsg->hwnd == TriggerSort::Instance)
	{
		if (TriggerSort::Instance.OnMessage(pMsg))
			return TRUE;
	}
	

	return this->ppmfc::CFrameWnd::PreTranslateMessage(pMsg);
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

				TriggerSort::Instance.HideWindow();
				break;
			case TabPage::TriggerSort:
				this->DialogBar.ShowWindow(SW_HIDE);
				this->View.ShowWindow(SW_HIDE);

				TriggerSort::Instance.ShowWindow();
				if (CFinalSunDlg::Instance->TriggerFrame.m_hWnd)
				{
					if (!TreeView_GetCount(TriggerSort::Instance.GetHwnd()))
						TriggerSort::Instance.LoadAllTriggers();
				}
				break;
			}
			return TRUE;
		default:
			break;
		}
	}
	else if (lpNmhdr->hwndFrom == TriggerSort::Instance)
		if (TriggerSort::Instance.OnNotify(reinterpret_cast<LPNMTREEVIEW>(lpNmhdr)))
			return TRUE;
	return this->ppmfc::CFrameWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CTileSetBrowserFrameExt::OnCommandExt(WPARAM wParam, LPARAM lParam)
{
	return this->ppmfc::CFrameWnd::OnCommand(wParam, lParam);
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

	int i = 0;
	auto insertItem = [&](const char* lpszDefault, const char* lpszTranslate)
	{
		TCITEM pitem;
		pitem.mask = TCIF_TEXT;
		FA2sp::Buffer = lpszDefault;
		Translations::GetTranslationItem(lpszTranslate, FA2sp::Buffer);
		pitem.pszText = FA2sp::Buffer.m_pchData;
		TabCtrl_InsertItem(this->hTabCtrl, i++, &pitem);
	};

	insertItem("Tile placement", "TabPages.TilePlacement");
	insertItem("Trigger sort", "TabPages.TriggerSort");
	
	// Create the pages
	TriggerSort::Instance.Create(hTabCtrl);
	TriggerSort::Instance.HideWindow();
}