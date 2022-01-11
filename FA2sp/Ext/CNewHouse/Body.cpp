#include "Body.h"

CNewHouse* CNewHouseExt::Instance = nullptr;

void CNewHouseExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595950, &CNewHouseExt::PreTranslateMessageExt);
}

BOOL CNewHouseExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}