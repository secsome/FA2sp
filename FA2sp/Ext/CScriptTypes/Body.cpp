#include "Body.h"
#include "Functional.h"

#include <CMapData.h>
#include <CFinalSunDlg.h>

#include "../../Logger.h"
#include "../../Helpers/Helper.h"
#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

// WM_COMMAND
BOOL CScriptTypesExt::OnCommandExt(WPARAM wParam, LPARAM lParam)
{
	WORD wmID = LOWORD(wParam);
	WORD wmMsg = HIWORD(wParam);
	if (wmID == 6304)
		if (wmMsg == CBN_KILLFOCUS)
			this->OnCBExtraParamSelectChanged();
	

	return this->FA2CDialog::OnCommand(wParam, lParam);
}

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
		elif (pMsg->hwnd == this->GetDlgItem(6305)->GetSafeHwnd())
			this->OnBNMoveUpClicked();
		elif (pMsg->hwnd == this->GetDlgItem(6306)->GetSafeHwnd())
			this->OnBNMoveDownClicked();
	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CScriptTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595FC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596010 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // param update

	RunTime::ResetMemoryContentAt(0x596130, &CScriptTypesExt::OnCommandExt);
	RunTime::ResetMemoryContentAt(0x596148, &CScriptTypesExt::PreTranslateMessageExt);
	RunTime::ResetMemoryContentAt(0x596174, &CScriptTypesExt::OnInitDialogExt);
}

void CScriptTypesExt::UpdateParams(int actionIndex)
{
	auto& action = CScriptTypeAction::ExtActions[actionIndex];
	auto& param = CScriptTypeParam::ExtParams[action.ParamCode_];
	switch (param.Param_)
	{
	default:
	case 0:
		this->CCBScriptParameter.DeleteAllStrings();
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
	if (param.Param_ < 0)
		CScriptTypesFunctions::CScriptTypes_LoadParams_TypeList(this->CCBScriptParameter, -param.Param_);

	this->CSTParameterOfSection.SetWindowText(param.Label_);
	this->CSTParameterOfSection.EnableWindow(action.Editable_);
	this->CCBScriptParameter.EnableWindow(action.Editable_);
	this->CETDescription.SetWindowText(action.Description_);

	if (ExtCurrentScript->IsExtraParamEnabled(actionIndex))
	{
		auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
		pCBExtra->EnableWindow(true);
		ExtCurrentScript->LoadExtraParamBox(*pCBExtra, actionIndex);
		
	}
	else
	{
		auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
		pCBExtra->EnableWindow(false);
		pCBExtra->SetCurSel(-1);
		pCBExtra->SetWindowText("");
	}
}

std::map<int, CScriptTypeAction> CScriptTypeAction::ExtActions;
std::map<int, CScriptTypeParam> CScriptTypeParam::ExtParams;
std::map<int, int> CScriptTypesExt::RealScriptID;
BOOL CScriptTypesExt::OnInitDialogExt()
{
	BOOL ret = FA2CDialog::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, "ScriptTypesTitle");

	Translations::TranslateItem(this, 50700, "ScriptTypesDesc");
	Translations::TranslateItem(this, 50701, "ScriptTypesSelectedScript");
	Translations::TranslateItem(this, 50702, "ScriptTypesName");
	Translations::TranslateItem(this, 50703, "ScriptTypesActions");
	Translations::TranslateItem(this, 50704, "ScriptTypesActionType");
	Translations::TranslateItem(this, 50705, "ScriptTypesActionDesc");

	Translations::TranslateItem(this, 1154, "ScriptTypesAddScript");
	Translations::TranslateItem(this, 1066, "ScriptTypesDelScript");
	Translations::TranslateItem(this, 6300, "ScriptTypesCloScript");
	Translations::TranslateItem(this, 1173, "ScriptTypesAddAction");
	Translations::TranslateItem(this, 1174, "ScriptTypesDelAction");
	Translations::TranslateItem(this, 1198, "ScriptTypesActionParam");
	Translations::TranslateItem(this, 6301, "ScriptTypesCloAction");
	Translations::TranslateItem(this, 6302, "ScriptTypesInsertMode");
	Translations::TranslateItem(this, 6303, "ScriptTypesExtraParam");
	Translations::TranslateItem(this, 6305, "ScriptTypesMoveUp");
	Translations::TranslateItem(this, 6306, "ScriptTypesMoveDown");

	this->CCBCurrentAction.DeleteAllStrings();

	// Initialize defaults
	/*const char** pNames = reinterpret_cast<const char**>(0x5D035C);
	const char** pDescriptions = reinterpret_cast<const char**>(0x5D0448);

	for (int i = 0; i < 59; ++i)
	{
		auto& curAction = CScriptTypeAction::ExtActions[i];
		curAction.Name_ = pNames[i];
		curAction.Description_ = pDescriptions[i];
		curAction.Editable_ = true;
		curAction.Hide_ = false;
		curAction.ParamCode_ = 0;
	}*/

	auto& fadata = CINI::FAData();

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
				CScriptTypeParam::ExtParams[id].Param_ = atoi((const char*)pParseBuffer[1]);
				SAFE_RELEASE(pParseBuffer[1]);
			case 1:
				CScriptTypeParam::ExtParams[id].Label_ = pParseBuffer[0];
				SAFE_RELEASE(pParseBuffer[0]);
			case 0:
				continue;
			}
		}
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
				CScriptTypeAction::ExtActions[id].Description_ = pParseBuffer[4];
				SAFE_RELEASE(pParseBuffer[4]);
			case 4:
				CScriptTypeAction::ExtActions[id].Editable_ = ParseBool((const char*)pParseBuffer[3]);
				SAFE_RELEASE(pParseBuffer[3]);
			case 3:
				CScriptTypeAction::ExtActions[id].Hide_ = ParseBool((const char*)pParseBuffer[2]);
				SAFE_RELEASE(pParseBuffer[2]);
			case 2:
				CScriptTypeAction::ExtActions[id].ParamCode_ = atoi((const char*)pParseBuffer[1]);
				SAFE_RELEASE(pParseBuffer[1]);
			case 1:
				CScriptTypeAction::ExtActions[id].Name_ = pParseBuffer[0];
				SAFE_RELEASE(pParseBuffer[0]);
			case 0:
				continue;
			}
		}
	}

	for (auto& ent : CScriptTypeAction::ExtActions)
	{
		if (!ent.second.Hide_)
		{
			int data = CCBCurrentAction.AddString(ent.second.Name_);
			ent.second.PosInComboBox = data;
			RealScriptID[data] = ent.first;
		}
	}

	auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
	pCBExtra->DeleteAllStrings();

	ExtCurrentScript = new CurrentScript;
	ExtCurrentScript->Unset();

	return TRUE;
}

void CScriptTypesExt::UpdateDialog()
{
	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	STDHelpers::TrimIndex(currentID);

	this->CCBCurrentScript.DeleteAllStrings();

	auto& ini = CINI::CurrentDocument();

	if (auto pSection = ini.GetSection("ScriptTypes"))
		for (auto& pair : pSection->EntitiesDictionary)
			if (auto pName = ini.TryGetString(pair.second, "Name"))
			{
				FA2sp::Buffer.Format("%s (%s)", pair.second, *pName);
				this->CCBCurrentScript.AddString(FA2sp::Buffer);
			}

	auto nIndex = this->CCBCurrentScript.FindString(0, currentID);
	this->CCBCurrentScript.SetCurSel(nIndex);

	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
}

void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
{
	while (this->CLBScriptActions.DeleteString(0) != LB_ERR);
	
	int index = this->CCBCurrentScript.GetCurSel();
	if (index == CB_ERR)
		return;

	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	STDHelpers::TrimIndex(currentID);

	ExtCurrentScript->Set(currentID);
	for (int i = 0; i < ExtCurrentScript->Count; ++i)
	{
		if (ExtCurrentScript->IsExtraParamEnabledAtLine(i))
			FA2sp::Buffer.Format("[%d] : %d - (%d, %d)", i,
				ExtCurrentScript->Actions[i].Type,
				ExtCurrentScript->Actions[i].ParamNormal,
				ExtCurrentScript->Actions[i].ParamExt);
		else
			FA2sp::Buffer.Format("[%d] : %d - %d", i, 
				ExtCurrentScript->Actions[i].Type, 
				ExtCurrentScript->Actions[i].Param);

		this->CLBScriptActions.AddString(FA2sp::Buffer);
	}

	this->GetDlgItem(1010)->SetWindowText(ExtCurrentScript->Name);
	this->CLBScriptActions.SetCurSel(LB_ERR);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
}

void CScriptTypesExt::OnLBScriptActionsSelectChanged()
{
	int index = this->CLBScriptActions.GetCurSel();
	if (this->CCBCurrentScript.GetCurSel() == CB_ERR)
	{
		ExtCurrentScript->Unset();
		return;
	}
	if (index == LB_ERR)
		return;

	auto& ini = CINI::CurrentDocument();
	
	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	STDHelpers::TrimIndex(currentID);

	auto& currentAction = ExtCurrentScript->Actions[index];
	this->CCBCurrentAction.SetCurSel(CScriptTypeAction::ExtActions[currentAction.Type].PosInComboBox);

	this->CScriptTypesExt::OnCBCurrentActionSelectChanged();
}

void CScriptTypesExt::OnETScriptNameChanged()
{
	reinterpret_cast<ppmfc::CWnd*>(this->GetDlgItem(1010))->GetWindowText(FA2sp::Buffer);
	
	int nCurSelIndex = this->CCBCurrentScript.GetCurSel();
	if (nCurSelIndex == CB_ERR)
		return;

	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	STDHelpers::TrimIndex(currentID);

	auto& ini = CINI::CurrentDocument();
	ini.WriteString(currentID, "Name", FA2sp::Buffer);
	ExtCurrentScript->Name = FA2sp::Buffer;

	this->CCBCurrentScript.DeleteString(nCurSelIndex);
	this->CCBCurrentScript.InsertString(nCurSelIndex, ExtCurrentScript->ToString());
	this->CCBCurrentScript.SetCurSel(nCurSelIndex);
}

void CScriptTypesExt::OnCBCurrentActionEditChanged()
{
	int nTypeIndex = this->CCBCurrentAction.GetCurSel();
	if (nTypeIndex == CB_ERR)
		return;

	int nActionIndex = this->CLBScriptActions.GetCurSel();
	if (nActionIndex == CB_ERR)
		return;

	auto& currentAction = ExtCurrentScript->Actions[nActionIndex];
	currentAction.Type = this->RealScriptID[nTypeIndex];
	this->UpdateParams(currentAction.Type);
	if (ExtCurrentScript->IsExtraParamEnabled(currentAction.Type))
	{
		auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
		FA2sp::Buffer.Format("%d", currentAction.ParamExt);
		pCBExtra->SetWindowText(FA2sp::Buffer);

		FA2sp::Buffer.Format("%d", currentAction.ParamNormal);
		this->CCBScriptParameter.SetWindowText(FA2sp::Buffer);
		this->CScriptTypesExt::OnCBExtraParamSelectChanged();
	}
	else
	{
		FA2sp::Buffer.Format("%d", currentAction.Param);
		this->CCBScriptParameter.SetWindowText(FA2sp::Buffer);
		this->CScriptTypesExt::OnCBScriptParameterSelectChanged();
	}
}

void CScriptTypesExt::OnCBCurrentActionSelectChanged()
{
	this->CScriptTypesExt::OnCBCurrentActionEditChanged();
}

void CScriptTypesExt::OnCBScriptParameterEditChanged()
{
	int index = this->CLBScriptActions.GetCurSel();
	if (this->CCBCurrentScript.GetCurSel() == CB_ERR || index == LB_ERR)
		return;

	int param;
	this->CCBScriptParameter.GetWindowText(FA2sp::Buffer);
	// STDHelpers::TrimIndex(FA2sp::Buffer); // not quite needed
	if (sscanf_s(FA2sp::Buffer, "%d", &param) == 1)
		if (ExtCurrentScript->IsExtraParamEnabledAtLine(index))
			ExtCurrentScript->Actions[index].ParamNormal = param;
		else
			ExtCurrentScript->Actions[index].Param = param;

	ExtCurrentScript->WriteLine(index);

	this->CLBScriptActions.DeleteString(index);
	if (ExtCurrentScript->IsExtraParamEnabledAtLine(index))
		FA2sp::Buffer.Format("[%d] : %d - (%d, %d)", index,
			ExtCurrentScript->Actions[index].Type,
			ExtCurrentScript->Actions[index].ParamNormal,
			ExtCurrentScript->Actions[index].ParamExt);
	else
		FA2sp::Buffer.Format("[%d] : %d - %d", index,
			ExtCurrentScript->Actions[index].Type,
			ExtCurrentScript->Actions[index].Param);

	this->CLBScriptActions.InsertString(index, FA2sp::Buffer);
	this->CLBScriptActions.SetCurSel(index);
}

void CScriptTypesExt::OnCBScriptParameterSelectChanged()
{
	this->CScriptTypesExt::OnCBScriptParameterEditChanged();
}

void CScriptTypesExt::OnBNAddActionClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int nActionIndex = this->CLBScriptActions.GetCurSel();

	bool bInsertMode = ::SendMessage(::GetDlgItem(*this, 6302), BM_GETCHECK, 0, 0) == BST_CHECKED;
	if (nActionIndex == LB_ERR && bInsertMode)
		return;

	int nAddIndex = bInsertMode ? nActionIndex : ExtCurrentScript->Count;
	ExtCurrentScript->AddActionAt(0, 0, nAddIndex);
	ExtCurrentScript->Write();

	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
	this->CLBScriptActions.SetCurSel(nAddIndex);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
}

void CScriptTypesExt::OnBNDeleteActionClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int index = this->CLBScriptActions.GetCurSel();
	if (this->CCBCurrentScript.GetCurSel() == CB_ERR || index == LB_ERR)
		return;

	if (MessageBox("Are you sure to delete this action?", "FA2sp", MB_YESNO) == IDYES)
	{
		ExtCurrentScript->RemoveActionAt(index);
		ExtCurrentScript->Write();
		this->OnCBCurrentScriptSelectChanged();
		this->CLBScriptActions.SetCurSel(index - 1);
	}
}

void CScriptTypesExt::OnBNAddScriptClicked()
{
	CINI::GetAvailableIndex(&FA2sp::Buffer);
	auto& ini = CINI::CurrentDocument();
	ini.WriteString(FA2sp::Buffer, "Name", "New script");
	ExtCurrentScript->Set(FA2sp::Buffer);
	int index = this->CCBCurrentScript.AddString(FA2sp::Buffer + " (New script)");
	CINI::GetAvailableKey(&FA2sp::Buffer, "ScriptTypes");
	ini.WriteString("ScriptTypes", FA2sp::Buffer, ExtCurrentScript->ID);
	this->CCBCurrentScript.SetCurSel(index);
	this->OnCBCurrentScriptSelectChanged();
}

void CScriptTypesExt::OnBNDeleteScriptClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int index = this->CCBCurrentScript.GetCurSel();
	if (index == CB_ERR)
		return;

	if (MessageBox("Are you sure to delete this script?", "FA2sp", MB_YESNO) == IDYES)
	{
		CINI::CurrentDocument->DeleteSection(this->ExtCurrentScript->ID);
		if (auto pScripts = CINI::CurrentDocument->GetSection("ScriptTypes"))
		{
			for (auto& pairs : pScripts->EntitiesDictionary)
				if (strcmp(pairs.second, this->ExtCurrentScript->ID) == 0)
					CINI::CurrentDocument->DeleteKey("ScriptTypes", pairs.first);
		}
		this->ExtCurrentScript->Unset();
		this->CCBCurrentScript.DeleteString(index);
		this->CCBCurrentScript.SetCurSel(index - 1);
		this->OnCBCurrentScriptSelectChanged();
	}
}

void CScriptTypesExt::OnBNCloneScriptClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	ExtCurrentScript->Write(*CINI::GetAvailableIndex(&FA2sp::Buffer), ExtCurrentScript->Name + " Clone");
	ExtCurrentScript->Set(FA2sp::Buffer);
	int index = this->CCBCurrentScript.AddString(FA2sp::Buffer + " (" + ExtCurrentScript->Name + ")");
	CINI::GetAvailableKey(&FA2sp::Buffer, "ScriptTypes");
	CINI::CurrentDocument->WriteString("ScriptTypes", FA2sp::Buffer, ExtCurrentScript->ID);
	this->CCBCurrentScript.SetCurSel(index);
	this->OnCBCurrentScriptSelectChanged();
}

void CScriptTypesExt::OnBNCloneItemClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int nActionIndex = this->CLBScriptActions.GetCurSel();
	if (nActionIndex == LB_ERR)
		return;

	bool bInsertMode = ::SendMessage(::GetDlgItem(*this, 6302), BM_GETCHECK, 0, 0) == BST_CHECKED;

	int nAddIndex = bInsertMode ? nActionIndex : ExtCurrentScript->Count;
	ExtCurrentScript->AddActionAt(ExtCurrentScript->Actions[nActionIndex], nAddIndex);
	ExtCurrentScript->Write();

	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
	this->CLBScriptActions.SetCurSel(nAddIndex);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
}

void CScriptTypesExt::OnBNMoveUpClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int nActionIndex = this->CLBScriptActions.GetCurSel();
	if (nActionIndex == LB_ERR || nActionIndex == 0) // already at the top
		return;

	std::swap(ExtCurrentScript->Actions[nActionIndex], ExtCurrentScript->Actions[nActionIndex - 1]);
	ExtCurrentScript->WriteLine(nActionIndex);
	ExtCurrentScript->WriteLine(nActionIndex - 1);

	this->CLBScriptActions.LockWindowUpdate();
	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
	this->CLBScriptActions.SetCurSel(nActionIndex - 1);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
	this->CLBScriptActions.UnlockWindowUpdate();
}

void CScriptTypesExt::OnBNMoveDownClicked()
{
	if (!ExtCurrentScript->IsAvailable())
		return;

	int nActionIndex = this->CLBScriptActions.GetCurSel();
	if (nActionIndex == LB_ERR || nActionIndex == ExtCurrentScript->Count - 1) // already at the bottom
		return;

	std::swap(ExtCurrentScript->Actions[nActionIndex], ExtCurrentScript->Actions[nActionIndex + 1]);
	ExtCurrentScript->WriteLine(nActionIndex);
	ExtCurrentScript->WriteLine(nActionIndex + 1);

	this->CLBScriptActions.LockWindowUpdate();
	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
	this->CLBScriptActions.SetCurSel(nActionIndex + 1);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
	this->CLBScriptActions.UnlockWindowUpdate();
}

void CScriptTypesExt::OnCBExtraParamEditChanged()
{
	int index = this->CLBScriptActions.GetCurSel();
	if (this->CCBCurrentScript.GetCurSel() == CB_ERR || index == LB_ERR)
		return;

	auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
	pCBExtra->GetWindowText(FA2sp::Buffer);
	ExtCurrentScript->Actions[index].ParamExt = atoi(FA2sp::Buffer);

	this->OnCBScriptParameterSelectChanged();
}

void CScriptTypesExt::OnCBExtraParamSelectChanged()
{
	this->OnCBExtraParamEditChanged();
}