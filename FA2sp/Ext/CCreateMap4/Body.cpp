#include "Body.h"

CCreateMap4* CCreateMap4Ext::Instance = nullptr;

void CCreateMap4Ext::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CCreateMap4Ext::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595770, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CCreateMap4Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}