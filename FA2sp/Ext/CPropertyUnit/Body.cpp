#include "Body.h"

CPropertyUnit* CPropertyUnitExt::Instance = nullptr;

void CPropertyUnitExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5985D0, &CPropertyUnitExt::PreTranslateMessageExt);
}

BOOL CPropertyUnitExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}