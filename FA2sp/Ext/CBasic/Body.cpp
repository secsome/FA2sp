#include "Body.h"

CBasic* CBasicExt::Instance = nullptr;

void CBasicExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592288, &CBasicExt::PreTranslateMessageExt);
}

BOOL CBasicExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}