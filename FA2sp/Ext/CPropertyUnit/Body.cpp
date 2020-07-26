#include "Body.h"

CPropertyUnit* CPropertyUnitExt::Instance = nullptr;

void CPropertyUnitExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CPropertyUnitExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x5985D0, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CPropertyUnitExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}