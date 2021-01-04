#include "Body.h"

CPropertyBuilding* CPropertyBuildingExt::Instance = nullptr;

void CPropertyBuildingExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto propertyBuildingPreTranslateAddr = &CPropertyBuildingExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x592388, &propertyBuildingPreTranslateAddr, sizeof(propertyBuildingPreTranslateAddr));
}

BOOL CPropertyBuildingExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

// TODO
// CACO TRY THIS, IT'S EASY
// Hook/Rewrite OnInitDialog
// 
// Powerups stupid error
// Houses Reader
//
// You can have a look on CScriptTypesExt as a reference
//
//BOOL CPropertyBuildingExt::OnInitDialogExt()
//{
//	if (!this->FA2CDialog::OnInitDialog())
//		return FALSE;
//
//	// INITIALIZE WORKS
//
//	return TRUE;
//}
//
//DEFINE_HOOK(417F40, CPropertyBuilding_OnInitDialog, 7)
//{
//	GET(CPropertyBuildingExt*, pThis, ECX);
//	R->EAX(pThis->CPropertyBuildingExt::OnInitDialogExt());
//
//	return 0x41A4AE;
//}