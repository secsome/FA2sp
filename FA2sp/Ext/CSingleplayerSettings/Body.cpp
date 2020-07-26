#include "Body.h"

CSingleplayerSettings* CSingleplayerSettingsExt::Instance = nullptr;

void CSingleplayerSettingsExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CSingleplayerSettingsExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596538, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CSingleplayerSettingsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}