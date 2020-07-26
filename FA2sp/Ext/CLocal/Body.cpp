#include "Body.h"

CLocal* CLocalExt::Instance = nullptr;

void CLocalExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto localPreTranslateAddr = &CLocalExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x593B18, &localPreTranslateAddr, sizeof(localPreTranslateAddr));
}

BOOL CLocalExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}