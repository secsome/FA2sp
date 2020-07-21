#include "Body.h"

CLoadingGraphics* CLoadingGraphicsExt::Instance = nullptr;

void CLoadingGraphicsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto loadingGraphicsPreTranslateAddr = &CLoadingGraphicsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592910, &loadingGraphicsPreTranslateAddr, sizeof(loadingGraphicsPreTranslateAddr));
}

BOOL CLoadingGraphicsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}