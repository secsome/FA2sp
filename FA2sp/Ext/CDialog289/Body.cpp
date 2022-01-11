#include "Body.h"

CDialog289* CDialog289Ext::Instance = nullptr;

void CDialog289Ext::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5926A8, &CDialog289Ext::PreTranslateMessageExt);
}

BOOL CDialog289Ext::PreTranslateMessageExt(MSG* pMsg)
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