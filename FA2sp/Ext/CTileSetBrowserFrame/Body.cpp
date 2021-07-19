#include "Body.h"

#include <GlobalVars.h>
#include "../../ExtraWindow/CTileManager/CTileManager.h"

void CTileSetBrowserFrameExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597458, &CTileSetBrowserFrameExt::PreTranslateMessageExt);
}


void CTileSetBrowserFrameExt::OnBNTileManagerClicked()
{
	if (GlobalVars::CurrentMapWidthPlusHeight())
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