#include "Body.h"

COptions* COptionsExt::Instance = nullptr;

void COptionsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5984E0, &COptionsExt::PreTranslateMessageExt);
}

BOOL COptionsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}