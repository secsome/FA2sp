#include "Body.h"

CSingleplayerSettings* CSingleplayerSettingsExt::Instance = nullptr;

void CSingleplayerSettingsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CSingleplayerSettingsExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x596538, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CSingleplayerSettingsExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}