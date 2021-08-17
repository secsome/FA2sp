#include "CAllieEditor.h"

#include <set>

#include "../../Helpers/STDHelpers.h"

#include "../../FA2sp.h"

void CAllieEditor::Create()
{
	DialogBox((HINSTANCE)FA2sp::hInstance, MAKEINTRESOURCE(303), GlobalVars::Dialogs::CFinalSunDlg->Houses, DlgProc);
}

BOOL CALLBACK CAllieEditor::DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	auto& cHouses = GlobalVars::Dialogs::CFinalSunDlg->Houses;

	switch (Msg)
	{
	case WM_INITDIALOG: {
		ppmfc::CString currentCountry;
		cHouses.CCBHouses.GetWindowText(currentCountry);
		currentCountry.Trim();
		HWND hLBAllies = GetDlgItem(hwnd, 6302);
		HWND hLBEnemies = GetDlgItem(hwnd, 6303);
		HWND hETCurrent = GetDlgItem(hwnd, 6304);

		std::set<ppmfc::CString> allies;
		cHouses.CETAllies.GetWindowText(FA2sp::Buffer);
		for (auto& str : STDHelpers::SplitString(FA2sp::Buffer))
			if (!STDHelpers::IsNullOrEmpty(str))
			{
				str.Trim();
				allies.insert(str);
			}
		
		for (int i = 0; i < cHouses.CCBHouses.GetCount(); ++i)
		{
			cHouses.CCBHouses.GetLBText(i, FA2sp::Buffer);
			FA2sp::Buffer.Trim();
			if (strcmp(FA2sp::Buffer, currentCountry) == 0)
				continue;
			if (allies.find(FA2sp::Buffer) != allies.end())
				SendMessage(hLBAllies, LB_ADDSTRING, NULL, (LPARAM)FA2sp::Buffer.m_pchData);
			else
				SendMessage(hLBEnemies, LB_ADDSTRING, NULL, (LPARAM)FA2sp::Buffer.m_pchData);
		}

		SetWindowText(hETCurrent, currentCountry);

		return TRUE;
	}
	case WM_COMMAND: {
		WORD ID = LOWORD(wParam);
		WORD CODE = HIWORD(wParam);
		if (CODE == BN_CLICKED)
		{
			switch (ID)
			{
			case IDOK: {
				ppmfc::CString allies = "";
				HWND LBA = GetDlgItem(hwnd, 6302);//Allies ListBox
				int cnt = SendMessage(LBA, LB_GETCOUNT, NULL, NULL);
				for (int i = 0; i < cnt - 1; ++i)
				{
					int TextLen = SendMessage(LBA, LB_GETTEXTLEN, i, NULL);
					if (TextLen == LB_ERR)	break;
					TCHAR* str = new TCHAR[TextLen + 1];
					SendMessage(LBA, LB_GETTEXT, i, (LPARAM)str);
					FA2sp::Buffer.Format("%s,", str);
					delete[] str;
					allies += FA2sp::Buffer;
				}
				int TextLen = SendMessage(LBA, LB_GETTEXTLEN, cnt - 1, NULL);
				if (TextLen == LB_ERR)	break;
				TCHAR* str = new TCHAR[TextLen + 1];
				SendMessage(LBA, LB_GETTEXT, cnt - 1, (LPARAM)str);
				FA2sp::Buffer.Format("%s", str);
				delete[] str;
				allies += FA2sp::Buffer;

				cHouses.CETAllies.SetWindowText(allies);
				EndDialog(hwnd, NULL);
				return TRUE;
			}
			case IDCANCEL: {
				EndDialog(hwnd, NULL);
				return TRUE;
			}
			case 6300: {//Go Allies
				HWND LBA = GetDlgItem(hwnd, 6302);//Allies ListBox
				HWND LBB = GetDlgItem(hwnd, 6303);//Enemy ListBox
				int EnemyCount = SendMessage(LBB, LB_GETCOUNT, NULL, NULL);
				if (EnemyCount <= 0)	break;
				int EnemyCurSelIndex = SendMessage(LBB, LB_GETCURSEL, NULL, NULL);
				if (EnemyCurSelIndex < 0 || EnemyCurSelIndex >= EnemyCount)	break;
				int TextLen = SendMessage(LBB, LB_GETTEXTLEN, EnemyCurSelIndex, NULL);
				if (TextLen == LB_ERR)	break;
				TCHAR* str = new TCHAR[TextLen + 1];
				SendMessage(LBB, LB_GETTEXT, EnemyCurSelIndex, (LPARAM)str);
				SendMessage(LBB, LB_DELETESTRING, EnemyCurSelIndex, NULL);
				SendMessage(LBA, LB_ADDSTRING, NULL, (LPARAM)str);
				delete[] str;
				break;
			}
			case 6301: {//Go Enemies
				HWND LBA = GetDlgItem(hwnd, 6302);//Allies ListBox
				HWND LBB = GetDlgItem(hwnd, 6303);//Enemy ListBox
				int AllieCount = SendMessage(LBA, LB_GETCOUNT, NULL, NULL);
				if (AllieCount <= 0)	break;
				int AllieCurSelIndex = SendMessage(LBA, LB_GETCURSEL, NULL, NULL);
				if (AllieCurSelIndex < 0 || AllieCurSelIndex >= AllieCount)	break;
				int TextLen = SendMessage(LBA, LB_GETTEXTLEN, AllieCurSelIndex, NULL);
				if (TextLen == LB_ERR)	break;
				TCHAR* str = new TCHAR[TextLen + 1];
				SendMessage(LBA, LB_GETTEXT, AllieCurSelIndex, (LPARAM)str);
				SendMessage(LBA, LB_DELETESTRING, AllieCurSelIndex, NULL);
				SendMessage(LBB, LB_ADDSTRING, NULL, (LPARAM)str);
				delete[] str;
				break;
			}
			default:
				break;
			}
		}
		else if (CODE == LBN_DBLCLK)
		{
			if (ID == 6303) // Go allies
			{
				HWND LBA = GetDlgItem(hwnd, 6302);//Allies ListBox
				HWND LBB = GetDlgItem(hwnd, 6303);//Enemy ListBox
				int EnemyCount = SendMessage(LBB, LB_GETCOUNT, NULL, NULL);
				if (EnemyCount <= 0)	break;
				int EnemyCurSelIndex = SendMessage(LBB, LB_GETCURSEL, NULL, NULL);
				if (EnemyCurSelIndex < 0 || EnemyCurSelIndex >= EnemyCount)	break;
				int TextLen = SendMessage(LBB, LB_GETTEXTLEN, EnemyCurSelIndex, NULL);
				if (TextLen == LB_ERR)	break;
				TCHAR* str = new TCHAR[TextLen + 1];
				SendMessage(LBB, LB_GETTEXT, EnemyCurSelIndex, (LPARAM)str);
				SendMessage(LBB, LB_DELETESTRING, EnemyCurSelIndex, NULL);
				SendMessage(LBA, LB_ADDSTRING, NULL, (LPARAM)str);
				delete[] str;
			}
			else if (ID == 6302) // Go Enemies
			{
				HWND LBA = GetDlgItem(hwnd, 6302);//Allies ListBox
				HWND LBB = GetDlgItem(hwnd, 6303);//Enemy ListBox
				int AllieCount = SendMessage(LBA, LB_GETCOUNT, NULL, NULL);
				if (AllieCount <= 0)	break;
				int AllieCurSelIndex = SendMessage(LBA, LB_GETCURSEL, NULL, NULL);
				if (AllieCurSelIndex < 0 || AllieCurSelIndex >= AllieCount)	break;
				int TextLen = SendMessage(LBA, LB_GETTEXTLEN, AllieCurSelIndex, NULL);
				if (TextLen == LB_ERR)	break;
				TCHAR* str = new TCHAR[TextLen + 1];
				SendMessage(LBA, LB_GETTEXT, AllieCurSelIndex, (LPARAM)str);
				SendMessage(LBA, LB_DELETESTRING, AllieCurSelIndex, NULL);
				SendMessage(LBB, LB_ADDSTRING, NULL, (LPARAM)str);
				delete[] str;
			}
		}
		break;
	}
	case WM_CLOSE: {
		EndDialog(hwnd, NULL);
		return TRUE;
	}
	}
	return FALSE;
}