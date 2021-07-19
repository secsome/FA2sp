#include "Body.h"

CCredits* CCreditsExt::Instance = nullptr;

void CCreditsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592810, &CCreditsExt::PreTranslateMessageExt);
}

BOOL CCreditsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}