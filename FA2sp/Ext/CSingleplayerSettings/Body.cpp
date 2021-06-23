#include "Body.h"

CSingleplayerSettings* CSingleplayerSettingsExt::Instance = nullptr;

void CSingleplayerSettingsExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596538, &CSingleplayerSettingsExt::PreTranslateMessageExt);
}

BOOL CSingleplayerSettingsExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}