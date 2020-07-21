#include "Body.h"

CINIEditor* CINIEditorExt::Instance = nullptr;

void CINIEditorExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto iniEditorPreTranslateAddr = &CINIEditorExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x591E38, &iniEditorPreTranslateAddr, sizeof(iniEditorPreTranslateAddr));
}

BOOL CINIEditorExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}