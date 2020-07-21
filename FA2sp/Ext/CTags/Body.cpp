#include "Body.h"

CTags* CTagsExt::Instance = nullptr;

void CTagsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto tagsPreTranslateAddr = &CTagsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x596A60, &tagsPreTranslateAddr, sizeof(tagsPreTranslateAddr));
}

BOOL CTagsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}