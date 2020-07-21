#include "Body.h"

CAITriggerTypesEnable* CAITriggerTypesEnableExt::Instance = nullptr;

void CAITriggerTypesEnableExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto aiTriggerTypesEnablePreTranslateAddr = &CAITriggerTypesEnableExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x591C70, &aiTriggerTypesEnablePreTranslateAddr, sizeof(aiTriggerTypesEnablePreTranslateAddr));
}

BOOL CAITriggerTypesEnableExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}