#include "Body.h"

CHouses* CHousesExt::Instance = nullptr;

void CHousesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto housesPreTranslateAddr = &CHousesExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x593DE8, &housesPreTranslateAddr, sizeof(housesPreTranslateAddr));
}

BOOL CHousesExt::PreTranslateMessageExt(MSG* pMsg)
{

	switch (pMsg->message) {
	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}
