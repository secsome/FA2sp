#include "Body.h"

CSaveOption* CSaveOptionExt::Instance = nullptr;

void CSaveOptionExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595E30, &CSaveOptionExt::PreTranslateMessageExt);
}

BOOL CSaveOptionExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}