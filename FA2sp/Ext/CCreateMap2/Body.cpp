#include "Body.h"

CCreateMap2* CCreateMap2Ext::Instance = nullptr;

void CCreateMap2Ext::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595470, &CCreateMap2Ext::PreTranslateMessageExt);
}

BOOL CCreateMap2Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}