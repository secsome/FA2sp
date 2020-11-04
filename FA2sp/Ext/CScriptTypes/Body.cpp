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

	while (::SendMessage(CCBCurrentAction, CB_DELETESTRING, 0, 0) != -1)
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
		::SendMessage(CCBCurrentAction, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)name.second);

	return bReturn;
}

void CScriptTypesExt::DoDataExchange(CDataExchange* pDX)
{
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