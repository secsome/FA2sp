#include "Body.h"
#include "Functional.h"

#include <Helpers/Macro.h>
#include <GlobalVars.h>

// Cleanning up
DEFINE_HOOK(4D5B20, CScriptTypes_DTOR, 7)
{
    auto& dict_1 = CScriptTypesExt::ExtActions;
    for (auto& x : dict_1)
    {
        delete[] x.second.Description_;
        delete[] x.second.Name_;
    }
    dict_1.clear();

    auto& dict_2 = CScriptTypesExt::ExtParams;
    for (auto& x : dict_2)
        delete[] x.second.Label_;

    return 0;
}

DEFINE_HOOK(4D6A10, CScriptTypes_OnCBCurrentActionEditChanged, 7)
{
    enum {end = 0x4D7569};

    GET(CScriptTypes*, pThis, ECX);
    INIClass* pDocument = INIMapFieldUpdate::UpdateMapFieldData(1);
    while (pThis->CCBScriptParameter.DeleteString(0) != -1);
    int lbCurSel = pThis->CLBScriptActions.GetCurSel();
    if (lbCurSel >= 0)
    {
        int scriptCurSel = pThis->CCBCurrentScript.GetCurSel();
        if (scriptCurSel < 0)
            return end;
        CString scriptId;
        pThis->CCBCurrentScript.GetLBText(scriptCurSel, scriptId);
        TrimIndex(scriptId);
        int actionCurSel = pThis->CCBCurrentAction.GetCurSel();
        if (actionCurSel < 0) 
            return end;
        int actionData = pThis->CCBCurrentAction.GetItemData(actionCurSel);
        CScriptTypeParam actionParam = 
            CScriptTypesExt::ExtParams[CScriptTypesExt::ExtActions[actionData].ParamCode_];
        pThis->CSTParameterOfSection.SetWindowTextA(actionParam.Label_);
        switch (actionParam.Param_)
        {
        default:
        case 0:
            break;
        case 1:
            CScriptTypes_LoadParams_Target(pThis->CCBScriptParameter);
            break;
        case 2:
            CScriptTypes_LoadParams_Waypoint(pThis->CCBScriptParameter);
            break;
        case 3:
            CScriptTypes_LoadParams_ScriptLine(
                pThis->CCBScriptParameter,
                pThis->CLBScriptActions.GetCount()
            );
            break;
        case 4:
            CScriptTypes_LoadParams_SplitGroup(pThis->CCBScriptParameter);
            break;
        case 5:
            CScriptTypes_LoadParams_GlobalVariables(pThis->CCBScriptParameter);
            break;
        case 6:
            CScriptTypes_LoadParams_ScriptTypes(
                pThis->CCBScriptParameter,
                pThis->CCBCurrentScript);
            break;
        case 18:
            CScriptTypes_LoadParams_TalkBubble(pThis->CCBScriptParameter);
            break;
        case 19:
            CScriptTypes_LoadParams_Status(pThis->CCBScriptParameter);
            break;
        }
    }
    return end;
}

DEFINE_HOOK(4D75EF, CScriptTypes_OnCBCurrentActionSelectChanged, A)
{
    GET(CScriptTypes*, pThis, ESI);
    int cursel = pThis->CCBCurrentAction.GetCurSel();
    if (cursel < 0)
        return 0x4D763A;
    int data = pThis->CCBCurrentAction.GetItemData(cursel);
    auto& dict = CScriptTypesExt::ExtActions;
    auto& itr = dict.find(data);
    R->EAX(itr == dict.end() ? "***NO DESCRIPTION***" : itr->second.Description_);
    return 0x4D7631;
}

DEFINE_HOOK(4D6621, CScriptTypes_OnLBScriptActionsSelectChanged_1, 6)
{
    GET(CScriptTypes*, pThis, ESI);
    int cnt = pThis->CCBCurrentAction.GetCount();
    int result = 0;
    if (cnt >= 0)
    {
        while (pThis->CCBCurrentAction.GetItemData(cnt) != R->EAX())
        {
            if (--cnt < 0)
                break;
        }
        result = cnt < 0 ? 0 : cnt;
    }
    R->EAX(result);
    return 0;
}

DEFINE_HOOK(4D6667, CScriptTypes_OnLBScriptActionsSelectChanged_2, 7)
{
    GET(CScriptTypes*, pThis, ESI);
    int cursel = pThis->CCBCurrentAction.GetCurSel();
    if (cursel < 0)
        return 0x4D669C;
    int itemdata = pThis->CCBCurrentAction.GetItemData(cursel);
    
    auto& dict = CScriptTypesExt::ExtActions;
    auto& itr = dict.find(itemdata);
    if (itr != dict.end())
        R->EDI<const char*>(itr->second.Description_);
    else
        return 0x4D669C;
    return 0x4D6693;
}

DEFINE_HOOK(4D8D20, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypesExt*, pThis, ECX);
    BOOL bResult = pThis->CScriptTypesExt::OnInitDialog();
    R->EAX<BOOL>(bResult);
    return 0x4D8E06;
}

// A bug fix, should be no longer used after replaced the process
DEFINE_HOOK(4D6E4D, CScriptTypeClass_OnCBCurrentActionEditChanged_Houses, 6)
{
    R->Stack(0x0, true);
    R->Stack(0x4, true);
    return 0;
}

//
//DEFINE_HOOK(4D5BE0, CScriptTypes_DoDataExchange, 8)
//{
//	return 0;
//
//	//GET(CScriptTypesExt*, pThis, ECX);
//	//GET_STACK(CDataExchange*, pDX, 4);
//	//pThis->CScriptTypesExt::DoDataExchange(pDX);
// //   return 0x4D5C65;
//}
//
//DEFINE_HOOK(4D5C70, CScriptTypes_GetMessageMap, 5)
//{
//	R->EAX<void*>(CScriptTypesExt::GetMessageMap());
//	return 0x4D5C75;
//}
//
//DEFINE_HOOK(4D61B0, CScriptTypes_OnCBCurrentScriptSelectChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnCBCurrentScriptSelectChanged();
//	return 0x4D64FD;
//}
//
//DEFINE_HOOK(4D6500, CScriptTypes_OnLBScriptActionsSelectChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnLBScriptActionsSelectChanged();
//	return 0x4D676C;
//}
//
//DEFINE_HOOK(4D6770, CScriptTypes_OnETScriptNameChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnETScriptNameChanged();
//	return 0x4D6A0D;
//}
//
//DEFINE_HOOK(4D6A10, CScriptTypes_OnCBCurrentActionEditChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnCBCurrentActionEditChanged();
//	return 0x4D7569;
//}
//
//DEFINE_HOOK(4D75D0, CScriptTypes_OnCBCurrentActionSelectChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnCBCurrentActionSelectChanged();
//	return 0x4D7662;
//}
//
//DEFINE_HOOK(4D7670, CScriptTypes_OnCBScriptParameterEditChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnCBScriptParameterEditChanged();
//	return 0x4D7A44;
//}
//
//DEFINE_HOOK(4D7A50, CScriptTypes_OnCBScriptParameterSelectChanged, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnCBScriptParameterSelectChanged();
//	return 0x4D7AB8;
//}
//
//DEFINE_HOOK(4D7AC0, CScriptTypes_OnBNAddActionClicked, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnBNAddActionClicked();
//	return 0x4D7DC7;
//}
//
//DEFINE_HOOK(4D7DD0, CScriptTypes_OnBNDeleteActionClicked, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnBNDeleteActionClicked();
//	return 0x4D8388;
//}
//
//DEFINE_HOOK(4D8390, CScriptTypes_OnBNAddScriptClicked, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnBNAddScriptClicked();
//	return 0x4D8721;
//}
//
//DEFINE_HOOK(4D8730, CScriptTypes_OnBNDeleteScriptClicked, 7)
//{
//	GET(CScriptTypesExt*, pThis, ECX);
//	pThis->CScriptTypesExt::OnBNDeleteScriptClicked();
//	return 0x4D8AB6;
//}
