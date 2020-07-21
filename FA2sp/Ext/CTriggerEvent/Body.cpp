#include "Body.h"

CTriggerEvent* CTriggerEventExt::Instance = nullptr;

void CTriggerEventExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CTriggerEventExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x597D0C, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CTriggerEventExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}