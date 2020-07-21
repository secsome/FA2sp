#include "Body.h"

CAITriggerTypes* CAITriggerTypesExt::Instance = nullptr;

void CAITriggerTypesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto aiTriggerTypesPreTranslateAddr = &CAITriggerTypesExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x591B08, &aiTriggerTypesPreTranslateAddr, sizeof(aiTriggerTypesPreTranslateAddr));
}

BOOL CAITriggerTypesExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}