#include "Body.h"

CCellTag* CCellTagExt::Instance = nullptr;

void CCellTagExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto iniEditorPreTranslateAddr = &CCellTagExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592478, &iniEditorPreTranslateAddr, sizeof(iniEditorPreTranslateAddr));
}

BOOL CCellTagExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}