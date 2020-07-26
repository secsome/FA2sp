#include "Body.h"

COptions* COptionsExt::Instance = nullptr;

void COptionsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &COptionsExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x5984E0, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL COptionsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}