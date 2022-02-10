#include "Body.h"

CSpecialFlags* CSpecialFlagsExt::Instance = nullptr;

void CSpecialFlagsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596898, &CSpecialFlagsExt::PreTranslateMessageExt);
}

BOOL CSpecialFlagsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}