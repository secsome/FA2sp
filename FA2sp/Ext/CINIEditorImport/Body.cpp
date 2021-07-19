#include "Body.h"

CINIEditorImport* CINIEditorImportExt::Instance = nullptr;

void CINIEditorImportExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x593F08, &CINIEditorImportExt::PreTranslateMessageExt);
}

BOOL CINIEditorImportExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}