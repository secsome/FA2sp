#include "Body.h"

CMMX* CMMXExt::Instance = nullptr;

void CMMXExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CMMXExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x595008, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CMMXExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}