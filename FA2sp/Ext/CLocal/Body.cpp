#include "Body.h"

CLocal* CLocalExt::Instance = nullptr;

void CLocalExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x593B18, &CLocalExt::PreTranslateMessageExt);
}

BOOL CLocalExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}