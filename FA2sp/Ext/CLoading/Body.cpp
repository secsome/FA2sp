#include "Body.h"

CLoading* CLoadingExt::Instance = nullptr;

void CLoadingExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CLoadingExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x5948A8, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CLoadingExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}