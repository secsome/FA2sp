#include "Body.h"

CEasterEgg* CEasterEggExt::Instance = nullptr;

void CEasterEggExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592A18, &CEasterEggExt::PreTranslateMessageExt);
}

BOOL CEasterEggExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}