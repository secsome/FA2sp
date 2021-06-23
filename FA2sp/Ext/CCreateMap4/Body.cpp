#include "Body.h"

CCreateMap4* CCreateMap4Ext::Instance = nullptr;

void CCreateMap4Ext::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595770, &CCreateMap4Ext::PreTranslateMessageExt);
}

BOOL CCreateMap4Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}