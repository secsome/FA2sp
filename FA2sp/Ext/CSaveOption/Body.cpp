#include "Body.h"

CSaveOption* CSaveOptionExt::Instance = nullptr;

void CSaveOptionExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CSaveOptionExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x595E30, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CSaveOptionExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}