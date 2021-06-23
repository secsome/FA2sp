#include "Body.h"

CChangeMapSize* CChangeMapSizeExt::Instance = nullptr;

void CChangeMapSizeExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592598, &CChangeMapSizeExt::PreTranslateMessageExt);
}

BOOL CChangeMapSizeExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}