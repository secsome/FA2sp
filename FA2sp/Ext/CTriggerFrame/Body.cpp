#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerFrameExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597BC4, &CTriggerFrameExt::OnInitDialogExt);
}

BOOL CTriggerFrameExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerFrame::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, "TriggerFrameTitle");

	Translations::TranslateItem(this, 50300, "TriggerFrameSelectedTrigger");

	Translations::TranslateItem(this, 1383, "TriggerFrameNew");
	Translations::TranslateItem(this, 1161, "TriggerFrameDel");
	Translations::TranslateItem(this, 1162, "TriggerFramePlace");
	Translations::TranslateItem(this, 1163, "TriggerFrameClone");

	return TRUE;
}

BOOL CTriggerFrameExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

DEFINE_HOOK(4CEC40, ASDUGVJBHASBDIHU, 7)
{
	Logger::Debug("ASGDVJHBAS\n");
	return 0;
}