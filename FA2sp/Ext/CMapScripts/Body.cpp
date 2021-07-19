#include "Body.h"

CMapScripts* CMapScriptsExt::Instance = nullptr;

void CMapScriptsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5986C4, &CMapScriptsExt::PreTranslateMessageExt);
}

BOOL CMapScriptsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}