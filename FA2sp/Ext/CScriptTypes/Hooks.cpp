#include "Body.h"

#include <Helpers/Macro.h>

DEFINE_HOOK(4D8D20, CScriptTypes_OnInitDialog, 6)
{
    GET(CScriptTypesExt*, pThis, ECX);
    BOOL bResult = pThis->CScriptTypesExt::OnInitDialog();
    R->EAX<BOOL>(bResult);
    return 0x4D8E06;
}

DEFINE_HOOK(4D5BE0, CScriptTypes_DoDataExchange, 8)
{
	return 0;

	//GET(CScriptTypesExt*, pThis, ECX);
	//GET_STACK(CDataExchange*, pDX, 4);
	//pThis->CScriptTypesExt::DoDataExchange(pDX);
 //   return 0x4D5C65;
}

DEFINE_HOOK(4D5C70, CScriptTypes_GetMessageMap, 5)
{
	R->EAX<void*>(CScriptTypesExt::GetMessageMap());
	return 0x4D5C75;
}
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
