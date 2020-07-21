#include "Body.h"

CPropertyInfantry* CPropertyInfantryExt::Instance = nullptr;

void CPropertyInfantryExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CPropertyInfantryExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592388, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CPropertyInfantryExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}