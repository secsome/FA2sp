#include "Body.h"

CLighting* CLightingExt::Instance = nullptr;

void CLightingExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto lightingPreTranslateAddr = &CLightingExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x594788, &lightingPreTranslateAddr, sizeof(lightingPreTranslateAddr));
}

BOOL CLightingExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}