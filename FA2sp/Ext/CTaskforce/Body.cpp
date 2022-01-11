#include "Body.h"

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

#include <CINI.h>

void CTaskForceExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596B38 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596B20 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // member count update
	RunTime::ResetMemoryContentAt(0x596BC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // group update
	RunTime::ResetMemoryContentAt(0x596B50 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // member type update

	RunTime::ResetMemoryContentAt(0x596CB4, &CTaskForceExt::OnInitDialogExt);
	RunTime::ResetMemoryContentAt(0x596C88, &CTaskForceExt::PreTranslateMessageExt);
}

BOOL CTaskForceExt::OnInitDialogExt()
{
	BOOL ret = this->CTaskForceExt::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, "TaskforceTitle");

	Translations::TranslateItem(this, 50800, "TaskforceList");
	Translations::TranslateItem(this, 50801, "TaskforceUnits");
	Translations::TranslateItem(this, 50802, "TaskforceGroup");
	Translations::TranslateItem(this, 50803, "TaskforceUnitNumber");
	Translations::TranslateItem(this, 50804, "TaskforceUnitType");
	Translations::TranslateItem(this, 50805, "TaskforceSelected");
	Translations::TranslateItem(this, 50806, "TaskforceName");
	
	Translations::TranslateItem(this, 1151, "TaskforceNewTask");
	Translations::TranslateItem(this, 1150, "TaskforceDelTask");
	Translations::TranslateItem(this, 50807, "TaskforceCloTask");
	Translations::TranslateItem(this, 1146, "TaskforceNewUnit");
	Translations::TranslateItem(this, 1147, "TaskforceDelUnit");
	Translations::TranslateItem(this, 50808, "TaskforceCloUnit");

	return TRUE;
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
		case WM_LBUTTONUP:
		{
			if (pMsg->hwnd == this->GetDlgItem(50807)->GetSafeHwnd())
				this->OnBNCloneTaskforceClicked();
		}
	}

	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}

void CTaskForceExt::OnBNCloneTaskforceClicked()
{
	if (this->CCBCurrentTaskforce.GetCount() > 0 && this->CCBCurrentTaskforce.GetCurSel() != CB_ERR)
	{
		ppmfc::CString currentID;
		this->CCBCurrentTaskforce.GetWindowText(currentID);
		STDHelpers::TrimIndex(currentID);

		ppmfc::CString key = CINI::GetAvailableKey("TaskForces");
		ppmfc::CString value = CINI::GetAvailableIndex();

		CINI::CurrentDocument->WriteString("TaskForces", key, value);
		
		for (int i = 0; i < this->CLBMembers.GetCount(); ++i)
		{
			key.Format("%d", i);
			auto data = CINI::CurrentDocument->GetString(currentID, key, "1,E1");
			CINI::CurrentDocument->WriteString(value, key, data);
		}
		auto name = CINI::CurrentDocument->GetString(currentID, "Name", "New Taskforce") + " Clone";
		CINI::CurrentDocument->WriteString(value, "Name", name);
		
		auto group = CINI::CurrentDocument->GetString(currentID, "Group", "-1");
		CINI::CurrentDocument->WriteString(value, "Group", group);

		int idx = this->CCBCurrentTaskforce.AddString(value + " (" + name + ")");
		this->CCBCurrentTaskforce.SetCurSel(idx);

		// this->OnCBCurrentTaskforceSelectChanged(); unnecessary, this is not needed for we should display them same thing
		this->SetDlgItemText(1010, name); // update the name huh
	}
}