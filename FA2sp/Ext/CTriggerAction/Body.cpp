#include "Body.h"

CTriggerAction* CTriggerActionExt::Instance = nullptr;

void CTriggerActionExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CTriggerActionExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x597A00, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CTriggerActionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}