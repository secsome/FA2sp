#include "Body.h"

CEasterEgg* CEasterEggExt::Instance = nullptr;

void CEasterEggExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto easterEggPreTranslateAddr = &CEasterEggExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x592A18, &easterEggPreTranslateAddr, sizeof(easterEggPreTranslateAddr));
}

BOOL CEasterEggExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}