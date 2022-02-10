#include "Body.h"

CINIEditor* CINIEditorExt::Instance = nullptr;

void CINIEditorExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591E38, &CINIEditorExt::PreTranslateMessageExt);
}

BOOL CINIEditorExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}