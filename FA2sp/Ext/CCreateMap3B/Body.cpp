#include "Body.h"

CCreateMap3B* CCreateMap3BExt::Instance = nullptr;

void CCreateMap3BExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595668, &CCreateMap3BExt::PreTranslateMessageExt);
}

BOOL CCreateMap3BExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}