#include "Body.h"

CCreateMap3A* CCreateMap3AExt::Instance = nullptr;

void CCreateMap3AExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CCreateMap3AExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x595560, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CCreateMap3AExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}