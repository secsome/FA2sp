#include "Body.h"

CMapScripts* CMapScriptsExt::Instance = nullptr;

void CMapScriptsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CMapScriptsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x597D0C, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CMapScriptsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}