#include "Body.h"

CINIEditor* CINIEditorExt::Instance = nullptr;

void CINIEditorExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto iniEditorPreTranslateAddr = &CINIEditorExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x591E38, &iniEditorPreTranslateAddr, sizeof(iniEditorPreTranslateAddr));
}

BOOL CINIEditorExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}