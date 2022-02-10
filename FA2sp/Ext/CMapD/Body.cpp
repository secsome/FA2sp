#include "Body.h"

CMapD* CMapDExt::Instance = nullptr;

void CMapDExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x594A40, &CMapDExt::PreTranslateMessageExt);
}

BOOL CMapDExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}