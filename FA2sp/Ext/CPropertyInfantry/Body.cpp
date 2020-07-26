#include "Body.h"

CPropertyInfantry* CPropertyInfantryExt::Instance = nullptr;

void CPropertyInfantryExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CPropertyInfantryExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x592388, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CPropertyInfantryExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}