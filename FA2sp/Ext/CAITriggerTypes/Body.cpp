#include "Body.h"

CAITriggerTypes* CAITriggerTypesExt::Instance = nullptr;

void CAITriggerTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591B08, CAITriggerTypesExt::PreTranslateMessageExt);
}

BOOL CAITriggerTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}