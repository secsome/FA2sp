#include "Body.h"

CNewHouse* CNewHouseExt::Instance = nullptr;

void CNewHouseExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CNewHouseExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x595950, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CNewHouseExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}