#include "Body.h"

CCreateMap1* CCreateMap1Ext::Instance = nullptr;

void CCreateMap1Ext::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CCreateMap1Ext::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595860, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CCreateMap1Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}