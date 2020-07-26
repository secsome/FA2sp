#include "Body.h"

CMapD* CMapDExt::Instance = nullptr;

void CMapDExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto mapdPreTranslateAddr = &CMapDExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x594A40, &mapdPreTranslateAddr, sizeof(mapdPreTranslateAddr));
}

BOOL CMapDExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}