#include "Body.h"

CScriptTypes* CScriptTypesExt::Instance = nullptr;

void CScriptTypesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto scripttypesPreTranslateAddr = &CScriptTypesExt::PreTranslateMessageHook;

	RunTime::ResetMemoryContentAt(0x596148, &scripttypesPreTranslateAddr, sizeof(scripttypesPreTranslateAddr));
}

BOOL CScriptTypesExt::PreTranslateMessageHook(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}