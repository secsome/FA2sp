#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

#include <CINI.h>

void CTriggerActionExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597A2C, &CTriggerActionExt::OnInitDialogExt);
	RunTime::ResetMemoryContentAt(0x597A00, &CTriggerActionExt::PreTranslateMessageExt);
}

BOOL CTriggerActionExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerAction::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, 50600, "TriggerActionCurrent");
	Translations::TranslateItem(this, 50601, "TriggerActionOptions");
	Translations::TranslateItem(this, 50602, "TriggerActionType");
	Translations::TranslateItem(this, 50603, "TriggerActionParameter");
	Translations::TranslateItem(this, 50604, "TriggerActionParamValue");
	Translations::TranslateItem(this, 50605, "TriggerActionDesc");

	Translations::TranslateItem(this, 1403, "TriggerActionNew");
	Translations::TranslateItem(this, 1174, "TriggerActionDel");
	Translations::TranslateItem(this, 50606, "TriggerActionClo");

	return TRUE;
}

BOOL CTriggerActionExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->GetDlgItem(50606)->GetSafeHwnd())
			this->OnBNCloneActionClicked();

	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CTriggerActionExt::OnBNCloneActionClicked()
{
	if (!this->ActionID.IsEmpty() && this->CCBCurrentAction.GetCount() > 0)
	{
		int nActionIndex = this->CCBCurrentAction.GetCurSel();
		if (nActionIndex != CB_ERR)
		{
			ppmfc::CString data = GlobalVars::INIFiles::CurrentDocument->GetString("Actions", this->ActionID);
			auto splitResults = STDHelpers::SplitString(data);
			int beginIndex = 1 + 8 * nActionIndex;
			int count = atoi(splitResults[0]);
			data.Format("%d,", count + 1);
			for (int i = 1; i < splitResults.size(); ++i)
			{
				data += splitResults[i];
				data += ",";
			}
			for (int i = 0; i < 7; ++i)
			{
				data += splitResults[beginIndex + i];
				data += ",";
			}
			data += splitResults[beginIndex + 7];
			GlobalVars::INIFiles::CurrentDocument->WriteString("Actions", this->ActionID, data);
			
			ppmfc::CString buffer;
			
			if (!Translations::GetTranslationItem("Action", data))
				data = "Action";

			buffer.Format("%s %d", data, count);
			int nNewIdx = this->CCBCurrentAction.AddString(buffer);
			this->CCBCurrentAction.SetItemData(nNewIdx, count);
			this->CCBCurrentAction.SetCurSel(nNewIdx);

			this->OnCBCurrentActionSelChanged();
		}
	}
}