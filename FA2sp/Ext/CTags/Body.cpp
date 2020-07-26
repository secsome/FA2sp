#include "Body.h"

CTags* CTagsExt::Instance = nullptr;

void CTagsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto tagsPreTranslateAddr = &CTagsExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596A60, &tagsPreTranslateAddr, sizeof(tagsPreTranslateAddr));
}

BOOL CTagsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}