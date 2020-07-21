#include "Body.h"

CEasterEgg* CEasterEggExt::Instance = nullptr;

void CEasterEggExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto easterEggPreTranslateAddr = &CEasterEggExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592A18, &easterEggPreTranslateAddr, sizeof(easterEggPreTranslateAddr));
}

BOOL CEasterEggExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}