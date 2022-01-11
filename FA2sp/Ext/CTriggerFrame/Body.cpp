#include "Body.h"

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

bool CTriggerFrameExt::CreateFromTriggerSort = false;

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
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}