#include "Body.h"

CPropertyInfantry* CPropertyInfantryExt::Instance = nullptr;

void CPropertyInfantryExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592388, &CPropertyInfantryExt::PreTranslateMessageExt);
}

BOOL CPropertyInfantryExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}