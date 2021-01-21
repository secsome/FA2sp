#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerOptionExt::ProgramStartupInit()
{
	/*auto addr = &CTeamTypesExt::PreTranslateMessageExt;
	RunTime::ResetMemoryContentAt(0x5971F8, &addr, 4);*/
	auto addr2 = &CTriggerOptionExt::OnInitDialogExt;
	RunTime::ResetMemoryContentAt(0x597F24, &addr2, 4);
}

BOOL CTriggerOptionExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerOption::OnInitDialog();
	if (!ret)
		return FALSE;

	auto TranslateDlgItem = [this](int nID, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			this->SetDlgItemText(nID, buffer);
	};

	auto TranslateCItem = [](CWnd* pWnd, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			pWnd->SetWindowText(buffer);
	};

	TranslateDlgItem(50400, "TriggerOptionType");
	TranslateDlgItem(50401, "TriggerOptionName");
	TranslateDlgItem(50402, "TriggerOptionHouse");
	TranslateDlgItem(50403, "TriggerOptionAttached");
	TranslateDlgItem(50404, "TriggerOptionDisabledDesc");

	TranslateDlgItem(1412, "TriggerOptionDisabled");
	TranslateDlgItem(1424, "TriggerOptionEasy");
	TranslateDlgItem(1425, "TriggerOptionMedium");
	TranslateDlgItem(1426, "TriggerOptionHard");
}

BOOL CTriggerOptionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}