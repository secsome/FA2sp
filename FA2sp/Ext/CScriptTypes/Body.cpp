#include "Body.h"
#include "Functional.h"

#include <GlobalVars.h>

#include "../../Logger.h"
#include "../../Helpers/Helper.h"

BOOL CScriptTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CScriptTypesExt::ProgramStartupInit()
{
	/*Logger::Debug(__FUNCTION__"\n");
	auto scripttypesPreTranslateAddr = &CScriptTypesExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596148, &scripttypesPreTranslateAddr, sizeof(scripttypesPreTranslateAddr));*/
}

int CScriptTypesExt::ExtParamID = -1;
void CScriptTypesExt::UpdateParams(int actionIndex)
{
	auto& action = ExtActions[actionIndex];
	auto& param = ExtParams[action.ParamCode_];
	if (param.Param_ == ExtParamID)
		return;
	switch (param.Param_)
	{
	default:
	case 0:
		while (this->CCBScriptParameter.DeleteString(0) != -1);
		break;
	case 1:
		CScriptTypes_LoadParams_Target(this->CCBScriptParameter);
		break;
	case 2:
		CScriptTypes_LoadParams_Waypoint(this->CCBScriptParameter);
		break;
	case 3:
		CScriptTypes_LoadParams_ScriptLine(
			this->CCBScriptParameter,
			this->CLBScriptActions.GetCount()
		);
		break;
	case 4:
		CScriptTypes_LoadParams_SplitGroup(this->CCBScriptParameter);
		break;
	case 5:
		CScriptTypes_LoadParams_GlobalVariables(this->CCBScriptParameter);
		break;
	case 6:
		CScriptTypes_LoadParams_ScriptTypes(this->CCBScriptParameter);
		break;
	case 7:
		CScriptTypes_LoadParams_TeamTypes(this->CCBScriptParameter);
		break;
	case 8:
		CScriptTypes_LoadParams_Houses(this->CCBScriptParameter);
		break;
	case 9:
		CScriptTypes_LoadParams_Speechs(this->CCBScriptParameter);
		break;
	case 10:
		CScriptTypes_LoadParams_Sounds(this->CCBScriptParameter);
		break;
	case 11:
		CScriptTypes_LoadParams_Movies(this->CCBScriptParameter);
		break;
	case 12:
		CScriptTypes_LoadParams_Themes(this->CCBScriptParameter);
		break;
	case 13:
		CScriptTypes_LoadParams_Countries(this->CCBScriptParameter);
		break;
	case 14:
		CScriptTypes_LoadParams_LocalVariables(this->CCBScriptParameter);
		break;
	case 15:
		CScriptTypes_LoadParams_Facing(this->CCBScriptParameter);
		break;
	case 16:
		CScriptTypes_LoadParams_BuildingTypes(this->CCBScriptParameter);
		break;
	case 17:
		CScriptTypes_LoadParams_Animations(this->CCBScriptParameter);
		break;
	case 18:
		CScriptTypes_LoadParams_TalkBubble(this->CCBScriptParameter);
		break;
	case 19:
		CScriptTypes_LoadParams_Status(this->CCBScriptParameter);
		break;
	}
	this->CSTParameterOfSection.SetWindowText(param.Label_);
	this->CSTParameterOfSection.EnableWindow(action.Editable_);
	this->CCBScriptParameter.EnableWindow(action.Editable_);
	this->CETDescription.SetWindowText(action.Description_);
	ExtParamID = param.Param_;
}

//
// Ext Functions
//

std::map<int, CScriptTypeAction> CScriptTypesExt::ExtActions;
std::map<int, CScriptTypeParam> CScriptTypesExt::ExtParams;
BOOL CScriptTypesExt::OnInitDialog()
{
	BOOL bReturn = FA2CDialog::OnInitDialog();
	if (bReturn)
	{
		while (CCBCurrentAction.DeleteString(0) != -1);

		// Initialize defaults
		const char** pNames = reinterpret_cast<const char**>(0x5D035C);
		const char** pDescriptions = reinterpret_cast<const char**>(0x5D0448);
		for (int i = 0; i < 59; ++i)
		{
			auto& curAction = ExtActions[i];
			curAction.Name_ = _strdup(pNames[i]);
			curAction.Description_ = _strdup(pDescriptions[i]);
			curAction.Editable_ = true;
			curAction.Hide_ = false;
			curAction.ParamCode_ = 0;
		}

		auto& fadata = GlobalVars::INIFiles::FAData();
		
		if (fadata.SectionExists("ScriptParams"))
		{
			auto& entities = fadata.GetSection("ScriptParams");
			char* pParseBuffer[2];
			for (auto& pair : entities.EntriesDictionary)
			{
				int id = atoi(pair.first);
				if (id < 0) continue;
				auto count =
					ParseList(pair.second, (const char**)(pParseBuffer), 2);
				switch (count)
				{
				default:
				case 2:
					ExtParams[id].Param_ = atoi((const char*)pParseBuffer[1]);
				case 1:
					ExtParams[id].Label_ = _strdup((const char*)pParseBuffer[0]);
				case 0:
					continue;
				}
			}
            SAFE_RELEASE(pParseBuffer[0]);
            SAFE_RELEASE(pParseBuffer[1]);
		}
		
		if (fadata.SectionExists("ScriptsRA2")) {
			auto& entities = fadata.GetSection("ScriptsRA2");
			char* pParseBuffer[5];
			for (auto& pair : entities.EntriesDictionary)
			{
				int id = atoi(pair.first);
				if (id < 0) continue;
				auto count =
					ParseList(pair.second, (const char**)(pParseBuffer), 5);
				switch (count)
				{
				case 5:
				default:
					ExtActions[id].Description_ = _strdup((const char*)pParseBuffer[4]);
				case 4:
					ExtActions[id].Editable_ = ParseBool((const char*)pParseBuffer[3]);
				case 3:
					ExtActions[id].Hide_ = ParseBool((const char*)pParseBuffer[2]);
				case 2:
					ExtActions[id].ParamCode_ = atoi((const char*)pParseBuffer[1]);
				case 1:
					ExtActions[id].Name_ = _strdup((const char*)pParseBuffer[0]);
				case 0:
					continue;
				}
			}
            SAFE_RELEASE(pParseBuffer[0]);
            SAFE_RELEASE(pParseBuffer[1]);
            SAFE_RELEASE(pParseBuffer[2]);
            SAFE_RELEASE(pParseBuffer[3]);
            SAFE_RELEASE(pParseBuffer[4]);
        }

        int counter = 0;
		for (auto& ent : ExtActions)
		{
			if (!ent.second.Hide_)
			{
				int data = CCBCurrentAction.AddString(ent.second.Name_);
				CCBCurrentAction.SetItemData(data, counter);
			}
            ++counter;
		}

	}
	return bReturn;
}

//
//void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
//{
//}
//
void CScriptTypesExt::OnLBScriptActionsSelectChanged()
{
	auto& doc = GlobalVars::INIFiles::CurrentDocument();
	CString scriptId ,buffer, tmp;
	int scriptIndex, listIndex, actionIndex, selectIndex, L, R, M;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		TrimIndex(scriptId);
		buffer.Format("%d", listIndex);
		buffer = doc.GetString(scriptId, buffer, "0,0");
		actionIndex = buffer.Find(',');
		if (actionIndex == CB_ERR)
		{
			buffer += ",0";
			actionIndex = buffer.GetLength() - 2;
		}
		tmp = buffer.Mid(actionIndex + 1);
		TrimIndex(tmp);
		this->CCBScriptParameter.SetWindowText(tmp);

		actionIndex = atoi(buffer.Mid(0, actionIndex));
		
		// As we know, the data sequence is ¡ü
		// So divide it!
		L = 0;
		R = this->CCBCurrentAction.GetCount() - 1;
		M = (L + R) >> 1;
		while (R > L)
		{
			const int MData = this->CCBCurrentAction.GetItemData(M);
			if (MData == actionIndex)
				break;
			if (MData > actionIndex)
				R = M;
			else
				L = M;
			M = (L + R) >> 1;
		}
		if (R > L)
			selectIndex = M;
		else
			selectIndex = 0;
		
		this->CCBCurrentAction.SetCurSel(selectIndex);
		this->UpdateParams(actionIndex);
	}
}
//
//void CScriptTypesExt::OnETScriptNameChanged()
//{
//}
//
void CScriptTypesExt::OnCBCurrentActionEditChanged()
{
	auto& doc = *INIMapFieldUpdate::UpdateMapFieldData(1);
	CString scriptId, buffer, listStr, tmp;
	int scriptIndex, listIndex, actionIndex, actionData;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		TrimIndex(scriptId);
		buffer.Format("%d", listIndex);
		buffer = doc.GetString(scriptId, buffer, "0,0");
		actionIndex = buffer.Find(',');
		if (actionIndex == CB_ERR)
			buffer = "0";
		else
			buffer = buffer.Mid(actionIndex + 1);

		actionIndex = this->CCBCurrentAction.GetCurSel();
		if (actionIndex >= 0)
		{
			actionData = this->CCBCurrentAction.GetItemData(actionIndex);
			this->UpdateParams(actionData);
			actionIndex = this->CCBScriptParameter.FindString(0, buffer);
			if (actionIndex != CB_ERR)
				this->CCBScriptParameter.SetCurSel(actionIndex);
			tmp.Format("%d,%s", actionData, buffer);
			listStr.Format("%d", listIndex);
			doc.WriteString(scriptId, listStr, tmp);
		}
	}
}
//
//void CScriptTypesExt::OnCBCurrentActionSelectChanged()
//{
//}
//
void CScriptTypesExt::OnCBScriptParameterEditChanged()
{
	auto& doc = GlobalVars::INIFiles::CurrentDocument();
	CString scriptId, buffer, listStr, paramStr, tmp;
	int scriptIndex, listIndex, actionIndex;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		TrimIndex(scriptId);
		buffer.Format("%d", listIndex);
		buffer = doc.GetString(scriptId, buffer, "0,0");
		actionIndex = buffer.Find(',');
		if (actionIndex == CB_ERR)
			actionIndex = buffer.GetLength();
		buffer = buffer.Mid(0, actionIndex);
		this->CCBScriptParameter.GetWindowText(paramStr);
		TrimIndex(paramStr);
		tmp.Format("%s,%s", buffer, paramStr);
		listStr.Format("%d", listIndex);
		doc.WriteString(scriptId, listStr, tmp);
	}
}
//
//void CScriptTypesExt::OnCBScriptParameterSelectChanged()
//{
//}
//
//void CScriptTypesExt::OnBNAddActionClicked()
//{
//}
//
//void CScriptTypesExt::OnBNDeleteActionClicked()
//{
//}
//
//void CScriptTypesExt::OnBNAddScriptClicked()
//{
//}
//
//void CScriptTypesExt::OnBNDeleteScriptClicked()
//{
//}