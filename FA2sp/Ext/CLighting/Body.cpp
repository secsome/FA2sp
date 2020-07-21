#include "Body.h"

CLighting* CLightingExt::Instance = nullptr;

void CLightingExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto lightingPreTranslateAddr = &CLightingExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x594788, &lightingPreTranslateAddr, sizeof(lightingPreTranslateAddr));
}

BOOL CLightingExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}