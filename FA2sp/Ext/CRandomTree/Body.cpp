#include "Body.h"

CRandomTree* CRandomTreeExt::Instance = nullptr;

void CRandomTreeExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CRandomTreeExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x595D40, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CRandomTreeExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}