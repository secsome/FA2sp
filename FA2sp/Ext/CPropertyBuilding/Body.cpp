#include "Body.h"

CPropertyBuilding* CPropertyBuildingExt::Instance = nullptr;

void CPropertyBuildingExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto propertyBuildingPreTranslateAddr = &CPropertyBuildingExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x592388, &propertyBuildingPreTranslateAddr, sizeof(propertyBuildingPreTranslateAddr));
}

BOOL CPropertyBuildingExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}