#include "Body.h"

CINIEditorImport* CINIEditorImportExt::Instance = nullptr;

void CINIEditorImportExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto insertINIFilePreTranslateAddr = &CINIEditorImportExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x593F08, &insertINIFilePreTranslateAddr, sizeof(insertINIFilePreTranslateAddr));
}

BOOL CINIEditorImportExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}