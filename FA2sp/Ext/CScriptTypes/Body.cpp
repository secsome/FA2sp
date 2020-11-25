#include "Body.h"

#include <GlobalVars.h>
#include <Miscs/Miscs.h>

#include "../../Logger.h"
#include "../../Helpers/Parser.h"

#include <map>
#include <vector>

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

BOOL CScriptTypesExt::OnInitDialog()
{
	using ActionParamStructure = std::tuple<CString, int, bool, bool, CString>;

	BOOL bReturn = FA2CDialog::OnInitDialog();

	while (CCBCurrentAction.DeleteString(0) != -1)
		;

	constexpr int nOriginActionCount = 59;
	auto lpActionName = reinterpret_cast<const char**>(0x5D035C);

	std::map<int, CString> mActions;
	for (int i = 0; i < nOriginActionCount; ++i)
		mActions[i] = lpActionName[i];

	for (auto& name : mActions)
		CCBCurrentAction.AddString(name.second);

	

	return bReturn;
}
//
//void CScriptTypesExt::DoDataExchange(CDataExchange* pDX)
//{
//	this->FA2CDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, 1407, CETDescription);
//	DDX_Control(pDX, 1064, CCBCurrentAction);
//	DDX_Control(pDX, 1193, CCBCurrentScript);
//	DDX_Control(pDX, 1196, CCBScriptParameter);
//	DDX_Control(pDX, 1170, CLBScriptActions);
//	DDX_Text(pDX, 1010, CString_ScriptName);
//}
//
//void* CScriptTypesExt::GetMessageMap()
//{
//	struct _AFX_MSGMAP
//	{
//		const _AFX_MSGMAP* (PASCAL* pfnGetBaseMap)();
//		const AFX_MSGMAP_ENTRY* lpEntries;
//	};
//
//	static AFX_MSGMAP_ENTRY pMsgEntries[] =
//	{
//		// Originals
//		ON_CBN_EDITCHANGE(1193, OnCBCurrentActionEditChanged)
//		ON_CBN_SELCHANGE(1193, OnCBCurrentScriptSelectChanged)
//		ON_LBN_SELCHANGE(1170, OnLBScriptActionsSelectChanged)
//		ON_EN_CHANGE(1010, OnETScriptNameChanged)
//		ON_CBN_EDITCHANGE(1064, OnCBCurrentActionEditChanged)
//		ON_CBN_SELCHANGE(1064, OnCBCurrentActionSelectChanged)
//		ON_CBN_EDITCHANGE(1196, OnCBScriptParameterEditChanged)
//		ON_CBN_SELCHANGE(1196, OnCBScriptParameterSelectChanged)
//		ON_BN_CLICKED(1173, OnBNAddActionClicked)
//		ON_BN_CLICKED(1174, OnBNDeleteActionClicked)
//		ON_BN_CLICKED(1154, OnBNAddScriptClicked)
//		ON_BN_CLICKED(1066, OnBNDeleteScriptClicked)
//		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
//	};
//
//	static _AFX_MSGMAP pMsgMap =
//	{
//		(const _AFX_MSGMAP * (PASCAL*)())0x59A548,
//		pMsgEntries
//	};
//
//	return &pMsgMap;
//}
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
//void CScriptTypesExt::OnCBCurrentActionEditChanged()
//{
//}
//
//void CScriptTypesExt::OnCBCurrentActionSelectChanged()
//{
//}
//
//void CScriptTypesExt::OnCBScriptParameterEditChanged()
//{
//}
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