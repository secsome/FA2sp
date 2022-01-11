#include "Body.h"

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerOptionExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597F24, &CTriggerOptionExt::OnInitDialogExt);
}

BOOL CTriggerOptionExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerOption::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, 50400, "TriggerOptionType");
	Translations::TranslateItem(this, 50401, "TriggerOptionName");
	Translations::TranslateItem(this, 50402, "TriggerOptionHouse");
	Translations::TranslateItem(this, 50403, "TriggerOptionAttached");
	Translations::TranslateItem(this, 50404, "TriggerOptionDisabledDesc");
	
	Translations::TranslateItem(this, 1412, "TriggerOptionDisabled");
	Translations::TranslateItem(this, 1424, "TriggerOptionEasy");
	Translations::TranslateItem(this, 1425, "TriggerOptionMedium");
	Translations::TranslateItem(this, 1426, "TriggerOptionHard");

	return TRUE;
}

BOOL CTriggerOptionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}