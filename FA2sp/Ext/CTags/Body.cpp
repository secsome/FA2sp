#include "Body.h"

CTags* CTagsExt::Instance = nullptr;

void CTagsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596A60, &CTagsExt::PreTranslateMessageExt);
}

BOOL CTagsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}