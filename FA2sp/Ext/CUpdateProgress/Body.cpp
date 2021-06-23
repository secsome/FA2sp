#include "Body.h"

CUpdateProgress* CUpdateProgressExt::Instance = nullptr;

void CUpdateProgressExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595A40, &CUpdateProgressExt::PreTranslateMessageExt);
}

BOOL CUpdateProgressExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}