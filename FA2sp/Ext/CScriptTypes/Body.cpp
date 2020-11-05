#include "Body.h"

#include <GlobalVars.h>
#include <Miscs/Miscs.h>

#include "../../Logger.h"

#include <map>

CScriptTypeUnit::CScriptTypeUnit(const char* lpSrc)
{
	CString lpStr = lpSrc;
	lpStr.TrimLeft();
	lpStr.TrimRight();
	int bDisplay;
	int nCount = sscanf_s(lpSrc, "%d,%s,%d,%s,%d",
		&Index, Name, &ParamType, Description, &bDisplay);
	switch (nCount)
	{
	default:
	case 0:
	case 1:
	case 2:
		Index = -1;
		Name[0] = '\0';
		ParamType = -1;
		Description[0] = '\0';
		DisplayInList = false;
		break;
	case 3:
	case 4:
		DisplayInList = true;
		break;
	case 5:
		switch (toupper(static_cast<unsigned char>(*lpSrc)))
		{
		case '1':
		case 'T':
		case 'Y':
		default:
			DisplayInList = true;
			break;
		case '0':
		case 'F':
		case 'N':
			DisplayInList = false;
			break;
		}
	}
}

BOOL CScriptTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CScriptTypesExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto scripttypesPreTranslateAddr = &CScriptTypesExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596148, &scripttypesPreTranslateAddr, sizeof(scripttypesPreTranslateAddr));
}

//
// Ext Functions
//

BOOL CScriptTypesExt::OnInitDialog()
{
	BOOL bReturn = FA2CDialog::OnInitDialog();

	while (CCBCurrentAction.DeleteString(0) != -1)
		;

	constexpr int nOriginActionCount = 59;
	auto lpActionName = reinterpret_cast<const char**>(0x5D035C);

	std::map<int, CString> mActions;
	for (int i = 0; i < nOriginActionCount; ++i)
		mActions[i] = lpActionName[i];

	INIClass& fadata = GlobalVars::INIFiles::FAData();
	if (fadata.SectionExists("ScriptsRA2"))
	{
		INISection& section = fadata.GetSection("ScriptsRA2");
		for (auto& pairs : section.EntriesDictionary)
		{
			CScriptTypeUnit unit{ pairs.second };
			ExtMap[unit.Index] = unit;
		}
	}

	for (auto& unit : ExtMap)
	{
		if (mActions.find(unit.first) == mActions.end())
		{
			if (unit.second.DisplayInList)
				mActions[unit.first] = unit.second.Name;
		}
		else
		{
			if (unit.second.DisplayInList)
				mActions[unit.first] = unit.second.Name;
			else
				mActions.erase(unit.first);
		}
	}

	for (auto& name : mActions)
		CCBCurrentAction.AddString(name.second);

	return bReturn;
}

void CScriptTypesExt::DoDataExchange(CDataExchange* pDX)
{
	this->FA2CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, 1407, CETDescription);
	DDX_Control(pDX, 1064, CCBCurrentAction);
	DDX_Control(pDX, 1193, CCBCurrentScript);
	DDX_Control(pDX, 1196, CCBScriptParameter);
	DDX_Control(pDX, 1170, CLBScriptActions);
	DDX_Text(pDX, 1010, CString_ScriptName);
}

void* CScriptTypesExt::GetMessageMap()
{
	struct _AFX_MSGMAP
	{
		const _AFX_MSGMAP* (PASCAL* pfnGetBaseMap)();
		const AFX_MSGMAP_ENTRY* lpEntries;
	};

	static AFX_MSGMAP_ENTRY pMsgEntries[] =
	{
		// Originals
		//ON_CBN_EDITCHANGE(1193, OnCBCurrentActionEditChanged)
		ON_CBN_SELCHANGE(1193, OnCBCurrentScriptSelectChanged)
		ON_LBN_SELCHANGE(1170, OnLBScriptActionsSelectChanged)
		ON_EN_CHANGE(1010, OnETScriptNameChanged)
		ON_CBN_EDITCHANGE(1064, OnCBCurrentActionEditChanged)
		ON_CBN_SELCHANGE(1064, OnCBCurrentActionSelectChanged)
		ON_CBN_EDITCHANGE(1196, OnCBScriptParameterEditChanged)
		ON_CBN_SELCHANGE(1196, OnCBScriptParameterSelectChanged)
		ON_BN_CLICKED(1173, OnBNAddActionClicked)
		ON_BN_CLICKED(1174, OnBNDeleteActionClicked)
		ON_BN_CLICKED(1154, OnBNAddScriptClicked)
		ON_BN_CLICKED(1066, OnBNDeleteScriptClicked)
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
	};

	static _AFX_MSGMAP pMsgMap =
	{
		(const _AFX_MSGMAP * (PASCAL*)())0x59A548,
		pMsgEntries
	};

	return &pMsgMap;
}

void CScriptTypesExt::OnCBCurrentScriptSelectChanged()
{
}

void CScriptTypesExt::OnLBScriptActionsSelectChanged()
{
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

void CScriptTypesExt::OnBNAddActionClicked()
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