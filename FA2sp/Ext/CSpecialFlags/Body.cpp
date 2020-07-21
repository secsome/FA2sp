#include "Body.h"

CSpecialFlags* CSpecialFlagsExt::Instance = nullptr;

void CSpecialFlagsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CSpecialFlagsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x596898, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CSpecialFlagsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}