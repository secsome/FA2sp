#include "Body.h"

CCreateMap2* CCreateMap2Ext::Instance = nullptr;

void CCreateMap2Ext::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CCreateMap2Ext::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595470, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CCreateMap2Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}