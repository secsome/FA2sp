#include "Body.h"

#include <GlobalVars.h>
#include <Miscs/Miscs.h>

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