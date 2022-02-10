#include "Body.h"

CMMX* CMMXExt::Instance = nullptr;

void CMMXExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595008, &CMMXExt::PreTranslateMessageExt);
}

BOOL CMMXExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}