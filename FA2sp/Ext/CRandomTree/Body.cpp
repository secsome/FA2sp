#include "Body.h"

CRandomTree* CRandomTreeExt::Instance = nullptr;

void CRandomTreeExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595D40, &CRandomTreeExt::PreTranslateMessageExt);
}

BOOL CRandomTreeExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}