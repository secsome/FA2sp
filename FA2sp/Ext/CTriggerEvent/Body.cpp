#include "Body.h"

CTriggerEvent* CTriggerEventExt::Instance = nullptr;

void CTriggerEventExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CTriggerEventExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x597D18, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CTriggerEventExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}