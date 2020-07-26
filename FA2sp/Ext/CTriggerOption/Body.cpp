#include "Body.h"

CTriggerOption* CTriggerOptionExt::Instance = nullptr;

void CTriggerOptionExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CTriggerOptionExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x597EF8, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CTriggerOptionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}