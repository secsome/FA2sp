#include "Body.h"

CScriptsSelectionDialog* CScriptsSelectionDialogExt::Instance = nullptr;

void CScriptsSelectionDialogExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5926A8, &CScriptsSelectionDialogExt::PreTranslateMessageExt);
}

BOOL CScriptsSelectionDialogExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {
	case WM_CREATE:
		Logger::Debug(__FUNCTION__"\n");
		break;
	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}