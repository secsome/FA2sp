#include "Body.h"

CCellTag* CCellTagExt::Instance = nullptr;

void CCellTagExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592478, &CCellTagExt::PreTranslateMessageExt);
}

BOOL CCellTagExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}