#include "Body.h"

CMapScripts* CMapScriptsExt::Instance = nullptr;

void CMapScriptsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CMapScriptsExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x5986C4, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CMapScriptsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}