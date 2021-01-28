#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerEventExt::ProgramStartupInit()
{
	auto addr2 = &CTriggerEventExt::OnInitDialogExt;
	RunTime::ResetMemoryContentAt(0x597D44, &addr2, 4);
}

BOOL CTriggerEventExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerEvent::OnInitDialog();
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

	TranslateDlgItem(50500, "TriggerEventCurrent");
	TranslateDlgItem(50501, "TriggerEventOptions");
	TranslateDlgItem(50502, "TriggerEventType");
	TranslateDlgItem(50503, "TriggerEventParameter");
	TranslateDlgItem(50504, "TriggerEventParamValue");
	TranslateDlgItem(50505, "TriggerEventDesc");

	TranslateDlgItem(1396, "TriggerEventNew");
	TranslateDlgItem(1169, "TriggerEventDel");

	return TRUE;
}

BOOL CTriggerEventExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}