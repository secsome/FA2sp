#include "Body.h"

#include <GlobalVars.h>

CScriptTypes* CScriptTypesExt::Instance = nullptr;

void CScriptTypesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto scripttypesPreTranslateAddr = &CScriptTypesExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596148, &scripttypesPreTranslateAddr, sizeof(scripttypesPreTranslateAddr));
}

BOOL CScriptTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

BOOL CScriptTypesExt::OnInitDialog() {
	this->FA2CDialog::OnInitDialog();

	while (this->CCBCurrentAction.DeleteString(0) != -1)
		continue;

	constexpr int FA2ActionNamesArraySize = 59;
	const char** pFA2ActionNamesArray = reinterpret_cast<const char**>(0x5D035C);
	for (int i = 0; i < FA2ActionNamesArraySize; ++i)
	{
		int idx = this->CCBCurrentAction.AddString(pFA2ActionNamesArray[i]);
		this->CCBCurrentAction.SetItemData(idx, i);
	}

	INIClass* pFAData = &GlobalVars::INIFiles::Rules.get();

	return TRUE;
}