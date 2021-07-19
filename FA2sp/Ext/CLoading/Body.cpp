#include "Body.h"

CLoading* CLoadingExt::Instance = nullptr;

void CLoadingExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5948A8, &CLoadingExt::PreTranslateMessageExt);
}

BOOL CLoadingExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}