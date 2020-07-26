#include "Body.h"

CCreateMap3B* CCreateMap3BExt::Instance = nullptr;

void CCreateMap3BExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CCreateMap3BExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595668, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CCreateMap3BExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}