#include "Body.h"

CChangeMapSize* CChangeMapSizeExt::Instance = nullptr;

void CChangeMapSizeExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto changeMapSizePreTranslateAddr = &CChangeMapSizeExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x592598, &changeMapSizePreTranslateAddr, sizeof(changeMapSizePreTranslateAddr));
}

BOOL CChangeMapSizeExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}