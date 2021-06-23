#include "Body.h"

CLoadingGraphics* CLoadingGraphicsExt::Instance = nullptr;

void CLoadingGraphicsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592910, &CLoadingGraphicsExt::PreTranslateMessageExt);
}

BOOL CLoadingGraphicsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}