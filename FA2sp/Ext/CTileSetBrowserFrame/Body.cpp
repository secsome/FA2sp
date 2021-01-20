#include "Body.h"

#include "../../ExtraWindow/CTileManager/CTileManager.h"

void CTileSetBrowserFrameExt::ProgramStartupInit()
{
	auto addr = &CTileSetBrowserFrameExt::PreTranslateMessageExt;
	RunTime::ResetMemoryContentAt(0x597458, &addr, 4);
}


void CTileSetBrowserFrameExt::OnBNTileManagerClicked()
{
	if (CTileManager::GetHandle() == NULL)
		CTileManager::Create(this);
	else
		::ShowWindow(CTileManager::GetHandle(), SW_SHOW);
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