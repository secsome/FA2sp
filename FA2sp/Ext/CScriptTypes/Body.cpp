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
            delete[] pParseBuffer[0];
            delete[] pParseBuffer[1];
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
            delete[] pParseBuffer[0];
            delete[] pParseBuffer[1];
            delete[] pParseBuffer[2];
            delete[] pParseBuffer[3];
            delete[] pParseBuffer[4];
		}

		for (auto& ent : ExtActions)
		{
			if (!ent.second.Hide_)
			{
				int data = CCBCurrentAction.AddString(ent.second.Name_);
				CCBCurrentAction.SetItemData(data, data);
			}
		}

	}
	return bReturn;
}

//
//void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
//{
//}
//
//void CScriptTypesExt::OnLBScriptActionsSelectChanged()
//{
//}
//
//void CScriptTypesExt::OnETScriptNameChanged()
//{
//}
//
void CScriptTypesExt::OnCBCurrentActionEditChanged()
{
    INIClass* pDocument = INIMapFieldUpdate::UpdateMapFieldData(1);
    while (this->CCBScriptParameter.DeleteString(0) != -1);
    int lbCurSel = this->CLBScriptActions.GetCurSel();
    if (lbCurSel >= 0)
    {
        int scriptCurSel = this->CCBCurrentScript.GetCurSel();
        if (scriptCurSel < 0)
            return;
        CString scriptId;
        this->CCBCurrentScript.GetLBText(scriptCurSel, scriptId);
        TrimIndex(scriptId);
        int actionCurSel = this->CCBCurrentAction.GetCurSel();
        if (actionCurSel < 0)
            return;
        int actionData = this->CCBCurrentAction.GetItemData(actionCurSel);
        CScriptTypeParam actionParam =
            CScriptTypesExt::ExtParams[CScriptTypesExt::ExtActions[actionData].ParamCode_];
        this->CSTParameterOfSection.SetWindowText(actionParam.Label_);
        switch (actionParam.Param_)
        {
        default:
        case 0:
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

        if (this->CLBScriptActions.GetCount() > 0 && lbCurSel >= 0)
        {
            CString index, result, buffer;
            index.Format("%d", lbCurSel);
            result = pDocument->GetString(scriptId, index, "0,0");
            int idx = result.ReverseFind(',') + 1;
            result = result.Mid(idx);
            buffer.Format("%d,%s", actionCurSel, result);
            pDocument->WriteString(scriptId, index, buffer);
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
    int lbCurSel = this->CLBScriptActions.GetCurSel();
    if (lbCurSel >= 0)
    {
        int scriptCurSel = this->CCBCurrentScript.GetCurSel();
        if (scriptCurSel < 0)
            return;
        CString scriptId;
        this->CCBCurrentScript.GetLBText(scriptCurSel, scriptId);
        TrimIndex(scriptId);
        int actionCurSel = this->CCBCurrentAction.GetCurSel();
        if (actionCurSel < 0)
            return;
        auto& doc = GlobalVars::INIFiles::CurrentDocument();
        if (this->CLBScriptActions.GetCount() > 0 && lbCurSel >= 0)
        {
            CString index, result, buffer;
            index.Format("%d", lbCurSel);
            this->CCBScriptParameter.GetWindowText(result);
            TrimIndex(result);
            buffer.Format("%d,%s", actionCurSel, result);
            doc.WriteString(scriptId, index, buffer);
        }
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