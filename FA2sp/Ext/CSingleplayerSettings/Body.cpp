#include "Body.h"

#include <CINI.h>

void CSingleplayerSettingsExt::ProgramStartupInit()
{
	//RunTime::ResetMemoryContentAt(0x596520, &CSingleplayerSettingsExt::OnCommandExt);
	RunTime::ResetMemoryContentAt(0x596538, &CSingleplayerSettingsExt::PreTranslateMessageExt);
}

//BOOL CSingleplayerSettingsExt::OnCommandExt(WPARAM wParam, LPARAM lParam)
//{
//	
//
//	return this->FA2CDialog::OnCommand(wParam, lParam);
//}


BOOL CSingleplayerSettingsExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == EN_KILLFOCUS || pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		auto process = [&pMsg, this](int nID, const char* pKey) -> bool // false for processed
		{
			auto pWnd = (ppmfc::CWnd*)this->GetDlgItem(nID);
			if (pMsg->hwnd == pWnd->m_hWnd)
			{
				ppmfc::CString buffer;
				pWnd->GetWindowText(buffer);
				CINI::CurrentDocument->WriteString("Ranking", pKey, buffer);
				return false;
			}
			return true;
		};
		
		bool flag = true;
		if (flag = process(1356, "ParTimeEasy"))
			if (flag = process(1357, "ParTimeMedium"))
				if (flag = process(1358, "ParTimeHard"))
					if (flag = process(1359, "OverParTitle"))
						if (flag = process(1360, "OverParMessage"))
							if (flag = process(1361, "UnderParTitle"))
								if (flag = process(1362, "UnderParMessage"))
									;
		if(!flag)
			return TRUE;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}