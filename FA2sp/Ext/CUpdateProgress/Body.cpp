#include "Body.h"

CUpdateProgress* CUpdateProgressExt::Instance = nullptr;

void CUpdateProgressExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CUpdateProgressExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595A40, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CUpdateProgressExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}