#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerEventExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597D44, &CTriggerEventExt::OnInitDialogExt);
}

BOOL CTriggerEventExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerEvent::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, 50500, "TriggerEventCurrent");
	Translations::TranslateItem(this, 50501, "TriggerEventOptions");
	Translations::TranslateItem(this, 50502, "TriggerEventType");
	Translations::TranslateItem(this, 50503, "TriggerEventParameter");
	Translations::TranslateItem(this, 50504, "TriggerEventParamValue");
	Translations::TranslateItem(this, 50505, "TriggerEventDesc");

	Translations::TranslateItem(this, 1396, "TriggerEventNew");
	Translations::TranslateItem(this, 1169, "TriggerEventDel");

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