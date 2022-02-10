#include "Body.h"

CCreateMap1* CCreateMap1Ext::Instance = nullptr;

void CCreateMap1Ext::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595860, &CCreateMap1Ext::PreTranslateMessageExt);
}

BOOL CCreateMap1Ext::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}