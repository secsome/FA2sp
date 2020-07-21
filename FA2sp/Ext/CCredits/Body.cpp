#include "Body.h"

CCredits* CCreditsExt::Instance = nullptr;

void CCreditsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto creditsPreTranslateAddr = &CCreditsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592810, &creditsPreTranslateAddr, sizeof(creditsPreTranslateAddr));
}

BOOL CCreditsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}