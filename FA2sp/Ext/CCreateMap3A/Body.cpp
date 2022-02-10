#include "Body.h"

CCreateMap3A* CCreateMap3AExt::Instance = nullptr;

void CCreateMap3AExt::ProgramStartupInit()
{

	RunTime::ResetMemoryContentAt(0x595560, &CCreateMap3AExt::PreTranslateMessageExt);
}

BOOL CCreateMap3AExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}