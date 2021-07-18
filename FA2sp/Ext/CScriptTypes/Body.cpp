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
		elif (pMsg->hwnd == this->GetDlgItem(6305)->GetSafeHwnd())
			this->OnBNMoveUpClicked();
		elif (pMsg->hwnd == this->GetDlgItem(6306)->GetSafeHwnd())
			this->OnBNMoveDownClicked();
	}
	elif (pMsg->message == WM_COMMAND)
	{
		WORD wmID = LOWORD(pMsg->wParam);
		WORD wmMsg = HIWORD(pMsg->wParam);
		if (wmID == 6304)
			if (wmMsg == CBN_EDITCHANGE)
				this->OnCBExtraParamEditChanged();
			elif (wmMsg == CBN_SELCHANGE)
				this->OnCBExtraParamSelectChanged();
	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CScriptTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x595FC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596010 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // param update

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

	if (actionIndex == 46 || actionIndex == 47 || actionIndex == 56 || actionIndex == 58)
	{
		auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
		pCBExtra->EnableWindow();
		pCBExtra->SetCurSel(0);
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

	while (CCBCurrentAction.DeleteString(0) != -1);

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
				CScriptTypeParam::ExtParams[id].Param_ = atoi((const char*)pParseBuffer[1]);
			case 1:
				CScriptTypeParam::ExtParams[id].Label_ = pParseBuffer[0];
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
				CScriptTypeAction::ExtActions[id].Description_ = pParseBuffer[4];
			case 4:
				CScriptTypeAction::ExtActions[id].Editable_ = ParseBool((const char*)pParseBuffer[3]);
			case 3:
				CScriptTypeAction::ExtActions[id].Hide_ = ParseBool((const char*)pParseBuffer[2]);
			case 2:
				CScriptTypeAction::ExtActions[id].ParamCode_ = atoi((const char*)pParseBuffer[1]);
			case 1:
				CScriptTypeAction::ExtActions[id].Name_ = pParseBuffer[0];
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
	for (auto& ent : CScriptTypeAction::ExtActions)
	{
		if (!ent.second.Hide_)
		{
			int data = CCBCurrentAction.AddString(ent.second.Name_);
			CCBCurrentAction.SetItemData(data, counter);
		}
		++counter;
	}

	auto pCBExtra = (ppmfc::CComboBox*)this->GetDlgItem(6304);
	while (pCBExtra->DeleteString(0) != CB_ERR);
	pCBExtra->SetItemData(pCBExtra->AddString("0 - Min Threat"), 0);
	pCBExtra->SetItemData(pCBExtra->AddString("1 - Max Threat"), 1);
	pCBExtra->SetItemData(pCBExtra->AddString("2 - Nearest"), 2);
	pCBExtra->SetItemData(pCBExtra->AddString("3 - Farest"), 3);

	return TRUE;
}

void CScriptTypesExt::UpdateDialog()
{
	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	currentID.Trim();

	while (this->CCBCurrentScript.DeleteString(0) != CB_ERR);

	auto& ini = GlobalVars::INIFiles::CurrentDocument();
	ppmfc::CString buffer;

	if (auto pSection = ini.GetSection("ScriptTypes"))
		for (auto& pair : pSection->EntitiesDictionary)
			if (auto pName = ini.TryGetString(pair.second, "Name"))
			{
				buffer.Format("%s (%s)", pair.second, *pName);
				this->CCBCurrentScript.AddString(buffer);
			}

	if (auto nIndex = this->CCBCurrentScript.FindStringExact(0, currentID))
		this->CCBCurrentScript.SetCurSel(nIndex);

	this->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
}

void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
{
	int index = this->CCBCurrentScript.GetCurSel();
	if (index == CB_ERR)
		return;

	ppmfc::CString currentID;
	this->CCBCurrentScript.GetWindowText(currentID);
	STDHelpers::TrimIndex(currentID);

	while (this->CLBScriptActions.DeleteString(0) != LB_ERR);
	ppmfc::CString buffer;

	ExtCurrentScript.Set(currentID);
	for (int i = 0; i < ExtCurrentScript.Count; ++i)
	{
		buffer.Format("[%d] : %d - %d", i, ExtCurrentScript.Actions[i].Type, ExtCurrentScript.Actions[i].Param);
		this->CLBScriptActions.AddString(buffer);
	}

	this->GetDlgItem(1010)->SetWindowText(ExtCurrentScript.Name);
	this->CLBScriptActions.SetCurSel(LB_ERR);
	this->CScriptTypesExt::OnLBScriptActionsSelectChanged();
}

void CScriptTypesExt::OnLBScriptActionsSelectChanged()
{
	int index = this->CLBScriptActions.GetCurSel();
	if (index == LB_ERR)
		return;

	/*int nType = ExtCurrentScript.Actions[index].Type;
	int nParam = ExtCurrentScript.Actions[index].Param;*/

	
}

void CScriptTypesExt::OnETScriptNameChanged()
{
}

void CScriptTypesExt::OnCBCurrentActionEditChanged()
{
}

void CScriptTypesExt::OnCBCurrentActionSelectChanged()
{
}

void CScriptTypesExt::OnCBScriptParameterEditChanged()
{
}

void CScriptTypesExt::OnCBScriptParameterSelectChanged()
{
}

void CScriptTypesExt::OnBNAddActionClickedExt()
{
}

void CScriptTypesExt::OnBNDeleteActionClicked()
{
}

void CScriptTypesExt::OnBNAddScriptClicked()
{
}

void CScriptTypesExt::OnBNDeleteScriptClicked()
{
}

void CScriptTypesExt::OnBNCloneScriptClicked()
{
}

void CScriptTypesExt::OnBNCloneItemClicked()
{
}

void CScriptTypesExt::OnBNMoveUpClicked()
{
}

void CScriptTypesExt::OnBNMoveDownClicked()
{
}

void CScriptTypesExt::OnCBExtraParamEditChanged()
{
}

void CScriptTypesExt::OnCBExtraParamSelectChanged()
{
}