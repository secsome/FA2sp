#include "Body.h"

CPropertyAircraft* CPropertyAircraftExt::Instance = nullptr;

void CPropertyAircraftExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto propertyAircraftPreTranslateAddr = &CPropertyAircraftExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x591698, &propertyAircraftPreTranslateAddr, sizeof(propertyAircraftPreTranslateAddr));
}

BOOL CPropertyAircraftExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}