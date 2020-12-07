#include "Body.h"

#include <Helpers/Macro.h>

// Cleanning up
DEFINE_HOOK(4D5B20, CScriptTypes_DTOR, 7)
{
    auto& dict = CScriptTypesExt::ExtActions;
    for (auto& x : dict)
    {
        delete x.second.Description_;
        delete x.second.Name_;
    }
    dict.clear();
    return 0;
}

// TODO
DEFINE_HOOK(43CE8D, Miscs_LoadParamToCombobox, 9)
{
    GET(CComboBox*, pComboBox, ESI);
    GET(int, nCode, EAX);
    while (pComboBox->DeleteString(0) != -1);
    
    enum {default = 0x43CE96, handled = 0x43D037};
    
    if (nCode < 40)
    {
        
    }
    return 0;
}

DEFINE_HOOK(4D8AC0, Miscs_LoadParams_EnterStatus, 5)
{
    GET_STACK(CComboBox*, pComboBox, 0x4);
    while (pComboBox->DeleteString(0) != -1);

    const char* pStatus[] =
    {
        "Sleep",
        "Attack nearest enemy",
        "Move",
        "QMove",
        "Retreat home for R&R",
        "Guard",
        "Sticky (never recruit)",
        "Enter object",
        "Capture object",
        "Move into & get eaten",
        "Harvest",
        "Area Guard",
        "Return (to refinery)",
        "Stop",
        "Ambush (wait until discovered)",
        "Hunt",
        "Unload",
        "Sabotage (move in & destroy)",
        "Construction",
        "Deconstruction",
        "Repair",
        "Rescue",
        "Missile",
        "Harmless",
        "Open",
        "Patrol",
        "Paradrop approach drop zone",
        "Paradrop overlay drop zone",
        "Wait",
        "Attack again",
        "Spyplane approach",
        "Spyplane overfly"
    };

    for (int i = 0; i < 32; ++i)
    {
        char buffer[0x40];
        sprintf_s(buffer, "%u - %s", i, pStatus[i]);
        int idx = pComboBox->AddString(buffer);
        if (idx >= 0)
            pComboBox->SetItemData(idx,i);
    }

    return 0x4D8D12;
}

DEFINE_HOOK(4463C0, Miscs_LoadParams_Attack, 6)
{
    GET_STACK(CComboBox*, pComboBox, 0x4);
    int nCurSel = pComboBox->GetCurSel();
    while (pComboBox->DeleteString(0) != -1);
    
    auto addString = [&pComboBox](const char* lpzStr, int data){
        int idx = pComboBox->AddString(lpzStr);
        if (idx >= 0)
            pComboBox->SetItemData(idx, data);
    };

    addString("0 - Not specified", 0);
    addString("1 - Anything (uses auto-targeting)", 1);
    addString("2 - Buildings", 2);
    addString("3 - Harvesters", 3);
    addString("4 - Infantry", 4);
    addString("5 - Vehicles", 5);
    addString("6 - Factories", 6);
    addString("7 - Base defenses", 7);
    addString("9 - Power plants", 9);
    addString("10 - Occupiables", 10);
    addString("11 - Tech Buildings", 11);

    if (nCurSel >= 0)
        pComboBox->SetCurSel(nCurSel);

    return 0x4464AB;
}

DEFINE_HOOK(4D75EF, CScriptTypes_OnParamEntered, A)
{
    GET(CScriptTypes*, pThis, ESI);
    int cursel = pThis->CCBCurrentAction.GetCurSel();
    if (cursel < 0)
        return 0x4D763A;
    int data = pThis->CCBCurrentAction.GetItemData(cursel);
    auto& dict = CScriptTypesExt::ExtActions;
    auto& itr = dict.find(data);
    R->EAX(itr == dict.end() ? "==NO DESCRIPTION==" : itr->second.Description_);
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
DEFINE_HOOK(4D6E4D, CScriptTypeClass_OnItemSelectChanged_Houses, 6)
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
