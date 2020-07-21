#include "Body.h"

CTeamTypes* CTeamTypesExt::Instance = nullptr;

void CTeamTypesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CTeamTypesExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x5971F8, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CTeamTypesExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}