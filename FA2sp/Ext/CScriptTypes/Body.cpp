#include "Body.h"

#include <GlobalVars.h>
#include <Miscs/Miscs.h>

#include "../../Logger.h"

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

BOOL CScriptTypesExt::ExtOnInitDialog() {
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

	INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();

	return TRUE;
}

int CScriptTypesExt::ExtOnActionUpdateParams() {

	enum {
		FAIL = 0,
		SUCCESS = 0x4D7182
	};

	//while (this->CCBScriptParameter.DeleteString(0) != -1)
	//	continue;
	//int nCurrentScriptIndex = this->CCBCurrentScript.GetCurSel();
	//if (nCurrentScriptIndex < 0)
	//	return FAIL;

	//CString strCurrentScriptString;
	//this->CCBCurrentScript.GetLBText(
	//	nCurrentScriptIndex, strCurrentScriptString);

	//Miscs::TrimIndex(strCurrentScriptString);

	int nCurrentActionIndex = this->CCBCurrentAction.GetCurSel();
	int nCurrentActionData = this->CCBCurrentAction.GetItemData(nCurrentActionIndex);

	CComboBox& ParamCbb = this->CCBScriptParameter;

	auto funcAddString = [](CComboBox& cbb,
		const char* string,
		int data)
	{
		int idx = cbb.AddString(string);
		if (idx > 0) cbb.SetItemData(idx, data);
	};

	switch (nCurrentActionData) {
	case 0:
	{	
		int nCurrentParam = ParamCbb.GetCurSel();
		while (ParamCbb.DeleteString(0) != -1)
			continue;
		
		funcAddString(ParamCbb, "0 - Not specified", 0);
		funcAddString(ParamCbb, "1 - Anything (uses auto-targeting)", 1);
		funcAddString(ParamCbb, "2 - Buildings", 2);
		funcAddString(ParamCbb, "3 - Harvesters", 3);
		funcAddString(ParamCbb, "4 - Infantry", 4);
		funcAddString(ParamCbb, "5 - Vehicles", 5);
		funcAddString(ParamCbb, "6 - Factories", 6);
		funcAddString(ParamCbb, "7 - Base defenses", 7);
		funcAddString(ParamCbb, "9 - Power plants", 9);
		funcAddString(ParamCbb, "10 - Occupiables", 10);
		funcAddString(ParamCbb, "11 - Tech Buildings", 11);

		if (ParamCbb.GetCount() > 0) {
			if (nCurrentParam < 0) nCurrentParam = 0;
			ParamCbb.SetCurSel(nCurrentParam);
		}

		this->CSTParameterOfSection.SetWindowText("Target");

		return SUCCESS;
	}
	case 52:
	{
		int nCurrentParam = ParamCbb.GetCurSel();

		while (ParamCbb.DeleteString(0) != -1)
			continue;

		funcAddString(ParamCbb, "0 - None", 0);
		funcAddString(ParamCbb, "1 - Asterisk(*)", 1);
		funcAddString(ParamCbb, "2 - Question mark(?)", 2);
		funcAddString(ParamCbb, "3 - Exclamation mark(!)", 3);

		this->CSTParameterOfSection.SetWindowText("Speech\nBubble:");
		return SUCCESS;
	}
	default:
		return FAIL;
	}
}