#include "Body.h"

CAITriggerTypesEnable* CAITriggerTypesEnableExt::Instance = nullptr;

void CAITriggerTypesEnableExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591C70, &CAITriggerTypesEnableExt::PreTranslateMessageExt);
}

BOOL CAITriggerTypesEnableExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}