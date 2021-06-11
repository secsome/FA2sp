#include "Body.h"
#include "Functional.h"

#include <GlobalVars.h>
#include <CMapData.h>
#include <CFinalSunDlg.h>

#include "../../Logger.h"
#include "../../Helpers/Helper.h"
#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

BOOL CScriptTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->GetDlgItem(6300)->GetSafeHwnd())
			this->OnBNCloneScriptClicked();
		elif (pMsg->hwnd == this->GetDlgItem(6301)->GetSafeHwnd())
			this->OnBNCloneItemClicked();
		elif (pMsg->hwnd == this->GetDlgItem(6302)->GetSafeHwnd())
		{
			bool bInsertMode = ::SendMessage(::GetDlgItem(*this, 6302), BM_GETCHECK, 0, 0) == BST_CHECKED;
			::SendMessage(::GetDlgItem(*this, 6302), BM_SETCHECK, bInsertMode ? BST_UNCHECKED : BST_CHECKED, 0);
		}
		/*elif (pMsg->hwnd == this->GetDlgItem(1173)->GetSafeHwnd())
		{
			this->OnBNAddActionClickedExt();
			return TRUE;
		}*/
			
	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CScriptTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595FC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596010 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // param update

	auto addr = &CScriptTypesExt::PreTranslateMessageExt;
	RunTime::ResetMemoryContentAt(0x596148, &addr, 4);
	auto addr2 = &CScriptTypesExt::OnInitDialogExt;
	RunTime::ResetMemoryContentAt(0x596174, &addr2, 4);
}

int CScriptTypesExt::ExtParamID = -1;
void CScriptTypesExt::UpdateParams(int actionIndex)
{
	auto& action = ExtActions[actionIndex];
	auto& param = ExtParams[action.ParamCode_];
	if (param.Param_ == ExtParamID) // tiny optimize
		return;
	switch (param.Param_)
	{
	default:
	case 0:
		while (this->CCBScriptParameter.DeleteString(0) != -1);
		break;
	case 1:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Target(this->CCBScriptParameter);
		break;
	case 2:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Waypoint(this->CCBScriptParameter);
		break;
	case 3:
		CScriptTypesFunctions::CScriptTypes_LoadParams_ScriptLine(
			this->CCBScriptParameter,
			this->CCBCurrentScript,
			this->CLBScriptActions
		);
		break;
	case 4:
		CScriptTypesFunctions::CScriptTypes_LoadParams_SplitGroup(this->CCBScriptParameter);
		break;
	case 5:
		CScriptTypesFunctions::CScriptTypes_LoadParams_GlobalVariables(this->CCBScriptParameter);
		break;
	case 6:
		CScriptTypesFunctions::CScriptTypes_LoadParams_ScriptTypes(this->CCBScriptParameter);
		break;
	case 7:
		CScriptTypesFunctions::CScriptTypes_LoadParams_TeamTypes(this->CCBScriptParameter);
		break;
	case 8:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Houses(this->CCBScriptParameter);
		break;
	case 9:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Speechs(this->CCBScriptParameter);
		break;
	case 10:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Sounds(this->CCBScriptParameter);
		break;
	case 11:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Movies(this->CCBScriptParameter);
		break;
	case 12:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Themes(this->CCBScriptParameter);
		break;
	case 13:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Countries(this->CCBScriptParameter);
		break;
	case 14:
		CScriptTypesFunctions::CScriptTypes_LoadParams_LocalVariables(this->CCBScriptParameter);
		break;
	case 15:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Facing(this->CCBScriptParameter);
		break;
	case 16:
		CScriptTypesFunctions::CScriptTypes_LoadParams_BuildingTypes(this->CCBScriptParameter);
		break;
	case 17:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Animations(this->CCBScriptParameter);
		break;
	case 18:
		CScriptTypesFunctions::CScriptTypes_LoadParams_TalkBubble(this->CCBScriptParameter);
		break;
	case 19:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Status(this->CCBScriptParameter);
		break;
	case 20:
		CScriptTypesFunctions::CScriptTypes_LoadParams_Boolean(this->CCBScriptParameter);
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
BOOL CScriptTypesExt::OnInitDialogExt()
{
	BOOL ret = FA2CDialog::OnInitDialog();
	if (!ret)
		return FALSE;

	auto TranslateDlgItem = [this](int nID, const char* lpKey)
	{
		ppmfc::CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			this->SetDlgItemText(nID, buffer);
	};

	auto TranslateCItem = [](CWnd* pWnd, const char* lpKey)
	{
		ppmfc::CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			pWnd->SetWindowText(buffer);
	};

	TranslateCItem(this, "ScriptTypesTitle");

	TranslateDlgItem(50700, "ScriptTypesDesc");
	TranslateDlgItem(50701, "ScriptTypesSelectedScript");
	TranslateDlgItem(50702, "ScriptTypesName");
	TranslateDlgItem(50703, "ScriptTypesActions");
	TranslateDlgItem(50704, "ScriptTypesActionType");
	TranslateDlgItem(1198, "ScriptTypesActionParam");//sbFA2
	TranslateDlgItem(50705, "ScriptTypesActionDesc");

	TranslateDlgItem(1154, "ScriptTypesAddScript");
	TranslateDlgItem(1066, "ScriptTypesDelScript");
	TranslateDlgItem(6300, "ScriptTypesCloScript");
	TranslateDlgItem(1173, "ScriptTypesAddAction");
	TranslateDlgItem(1174, "ScriptTypesDelAction");
	TranslateDlgItem(6301, "ScriptTypesCloAction");
	TranslateDlgItem(6302, "ScriptTypesInsertMode");

	while (CCBCurrentAction.DeleteString(0) != -1);

	// Initialize defaults
	const char** pNames = reinterpret_cast<const char**>(0x5D035C);
	const char** pDescriptions = reinterpret_cast<const char**>(0x5D0448);
	
	/*auto& errAct = ExtActions[-1];
	errAct.Description_ = "FA2sp Error Action Holder";
	errAct.Editable_ = false;
	errAct.Hide_ = true;
	errAct.Name_ = "INVALID SCRIPT ACTION";
	errAct.ParamCode_ = 0;*/

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

	if (auto entities = fadata.GetSection("ScriptParams"))
	{
		char* pParseBuffer[2];
		for (auto& pair : entities->EntitiesDictionary)
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

	if (auto entities = fadata.GetSection("ScriptsRA2"))
	{
		char* pParseBuffer[5];
		for (auto& pair : entities->EntitiesDictionary)
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
	return TRUE;
}

//
//void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
//{
//}
//
void CScriptTypesExt::OnLBScriptActionsSelectChanged()
{
	auto& doc = GlobalVars::INIFiles::CurrentDocument();
	ppmfc::CString scriptId ,buffer, tmp;
	int scriptIndex, listIndex, actionIndex, selectIndex, L, R, M;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		STDHelpers::TrimIndex(scriptId);
		buffer.Format("%d", listIndex);
		buffer = doc.GetString(scriptId, buffer, "0,0");
		actionIndex = buffer.Find(',');
		if (actionIndex == CB_ERR)
		{
			buffer += ",0";
			actionIndex = buffer.GetLength() - 2;
		}
		tmp = buffer.Mid(actionIndex + 1);
		STDHelpers::TrimIndex(tmp);
		this->CCBScriptParameter.SetWindowText(tmp);

		actionIndex = atoi(buffer.Mid(0, actionIndex));
		
		// Well, unnecessary but I want to do it.
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
	auto& doc = *GlobalVars::CMapData().UpdateCurrentDocument();
	ppmfc::CString scriptId, buffer, listStr, tmp;
	int scriptIndex, listIndex, actionIndex, actionData;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		STDHelpers::TrimIndex(scriptId);
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
	ppmfc::CString scriptId, buffer, listStr, paramStr, tmp;
	int scriptIndex, listIndex, actionIndex;

	scriptIndex = this->CCBCurrentScript.GetCurSel();
	listIndex = this->CLBScriptActions.GetCurSel();
	if (scriptIndex >= 0 && listIndex >= 0)
	{
		this->CCBCurrentScript.GetLBText(scriptIndex, scriptId);
		STDHelpers::TrimIndex(scriptId);
		buffer.Format("%d", listIndex);
		buffer = doc.GetString(scriptId, buffer, "0,0");
		actionIndex = buffer.Find(',');
		if (actionIndex == CB_ERR)
			actionIndex = buffer.GetLength();
		buffer = buffer.Mid(0, actionIndex);
		this->CCBScriptParameter.GetWindowText(paramStr);
		STDHelpers::TrimIndex(paramStr);
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
void CScriptTypesExt::OnBNAddActionClickedExt()
{
	/*if (this->CCBCurrentScript.GetCount() <= 0 && this->CCBCurrentScript.GetCurSel() < 0)
		return;

	bool bInsertMode = ::SendMessage(::GetDlgItem(*this, 6302), BM_GETCHECK, 0, 0) == BST_CHECKED;
	if (!bInsertMode)
	{
		this->OnBNAddActionClicked();
		return;
	}*/

	// insert mode ON
	/*CString scriptID;
	this->CCBCurrentScript.GetWindowText(scriptID);
	STDHelpers::TrimIndex(scriptID);

	auto& doc = GlobalVars::INIFiles::CurrentDocument();
	if (doc.SectionExists(scriptID))
	{
		int curIndex = this->CLBScriptActions.GetCurSel();
		int actionCount = this->CLBScriptActions.GetCount();
		this->OnBNAddActionClicked();

		if (actionCount <= 0)
			return;

		if (curIndex == CB_ERR)
			curIndex = 0;
		
		CString srcKey, destKey;

		for (int i = actionCount - 1; i >= curIndex; --i)
		{
			srcKey.Format("%d", i);
			destKey.Format("%d", i + 1);
			CString temp = doc.GetString(scriptID, srcKey, "0,0");
			Logger::Debug("%s %s %s %s\n", scriptID, srcKey, destKey, temp);
			doc.WriteString(scriptID, destKey, temp);
		}

		srcKey.Format("%d", curIndex);
		Logger::Debug("%s %s %s\n", scriptID, srcKey, "0,0");
		doc.WriteString(scriptID, srcKey, "0,0");
		this->OnCBCurrentScriptSelectChanged();
	}*/

	return;
}
//
//void CScriptTypesExt::OnBNDeleteActionClicked()
//{
//}
//
//void CScriptTypesExt::OnBNAddScriptClicked()
//{
//}
void CScriptTypesExt::OnBNAddScriptClickedExt()
{
	// TODO : Jump to the script we have just inserted!
}
//
//void CScriptTypesExt::OnBNDeleteScriptClicked()
//{
//}
void CScriptTypesExt::OnBNCloneScriptClicked()
{
	auto& doc = GlobalVars::INIFiles::CurrentDocument();

	int nCurSel = this->CCBCurrentScript.GetCurSel();
	if (nCurSel >= 0)
	{
		ppmfc::CString label;
		this->CCBCurrentScript.GetLBText(nCurSel, label);
		STDHelpers::TrimIndex(label);
		INISection copied(*doc.GetSection(label));
		ppmfc::CString name;
		name = copied.EntitiesDictionary["Name"];
		name += " Clone";
		((ppmfc::CString*)(&copied.EntitiesDictionary["Name"]))->AssignCopy(strlen(name), name);
		//Logger::Debug("new name = %s\n", name);
		ppmfc::CString id;
		id = INIClass::GetAvailableIndex();
		//Logger::Debug("available index get, id = %s\n", id);
		doc.InsertSection(id.operator LPCTSTR(), copied);
		/*Logger::Debug("section inserted!\n");
		Logger::Debug("section detail:\n");
		for (auto& x : copied.EntitiesDictionary)
			Logger::Debug("%s %s\n", x.first, x.second);*/
		ppmfc::CString key;
		key = INIClass::GetAvailableKey("ScriptTypes");
		//Logger::Debug("available section get, key = %s\n", key);
		doc.WriteString("ScriptTypes", key, id);
		//Logger::Debug("key inserted!\n");
		/*INISection& scripttypes = doc.GetSection("ScriptTypes");
		for (auto& x : scripttypes.EntitiesDictionary)
			Logger::Debug("%s %s\n", x.first, x.second);*/

		// objective : reload combobox
		auto& scripts = this->CCBCurrentScript;
		while (this->CCBCurrentScript.DeleteString(0) != CB_ERR)
			;
		auto scripttypes = doc.GetSection("ScriptTypes");
		for (auto& x : scripttypes->EntitiesDictionary)
			this->CCBCurrentScript.AddString((ppmfc::CString)x.second + " (" + doc.GetString(x.second, "Name") + ")");
		int idx = scripts.FindString(0, id);
		scripts.SetCurSel(idx);
		this->SetDlgItemText(1010, name);
	}
	return;
}
void CScriptTypesExt::OnBNCloneItemClicked()
{
	::MessageBox(NULL, "Haven't Implement!", "TODO", MB_OK);
}