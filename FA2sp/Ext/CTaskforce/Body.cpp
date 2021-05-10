#include "Body.h"

void CTaskForceExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596B38 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596B20 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // member count update
	RunTime::ResetMemoryContentAt(0x596BC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // group update
	RunTime::ResetMemoryContentAt(0x596B50 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // member type update

	RunTime::ResetMemoryContentAt(0x596C88, &CTaskForceExt::PreTranslateMessageExt);
}

BOOL CTaskForceExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message)
	{
		case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
			case VK_RETURN:
			{
				if (pMsg->hwnd == this->CCBMemberType.GetWindow(GW_CHILD)->m_hWnd)
					this->OnCBMemberTypeEditChanged();

				switch (::GetDlgCtrlID(pMsg->hwnd)) {
				case 1010: {this->OnETCurrentTaskforceEditChanged(); break; }
				case 1148: {this->OnETMemberCountEditChanged(); break; }
				case 1149: {this->OnETGroupEditChanged(); break; }
				default: break;
				}
			}
			return TRUE;

			default:
				break;
			}
		}


	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}
