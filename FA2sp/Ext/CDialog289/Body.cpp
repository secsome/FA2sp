#include "Body.h"

CDialog289* CDialog289Ext::Instance = nullptr;

void CDialog289Ext::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto multiAPreTranslateAddr = &CDialog289Ext::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x5926A8, &multiAPreTranslateAddr, sizeof(multiAPreTranslateAddr));
}

BOOL CDialog289Ext::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {
	case WM_CREATE:
		Logger::Debug(__FUNCTION__"\n");
		break;
	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}