#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerActionExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597A2C, &CTriggerActionExt::OnInitDialogExt);
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

	return TRUE;
}

BOOL CTriggerActionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}