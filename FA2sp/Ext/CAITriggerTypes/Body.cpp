#include "Body.h"

#include <CINI.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CAITriggerTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591B34, &CAITriggerTypesExt::OnInitDialogExt);
	RunTime::ResetMemoryContentAt(0x591B08, &CAITriggerTypesExt::PreTranslateMessageExt);
}

BOOL CAITriggerTypesExt::OnInitDialogExt()
{
	BOOL ret = this->CAITriggerTypes::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, "AITriggerTitle");
	Translations::TranslateItem(this, 50900, "AITriggerList");
	Translations::TranslateItem(this, 50901, "AITriggerName");
	Translations::TranslateItem(this, 50902, "AITriggerTeam1");
	Translations::TranslateItem(this, 50903, "AITriggerHouse");
	Translations::TranslateItem(this, 50904, "AITriggerTeam2");
	Translations::TranslateItem(this, 50905, "AITriggerTechlevel");
	Translations::TranslateItem(this, 50906, "AITriggerType");
	Translations::TranslateItem(this, 50907, "AITriggerWeight");
	Translations::TranslateItem(this, 50908, "AITriggerMinWeight");
	Translations::TranslateItem(this, 50909, "AITriggerMaxWeight");
	Translations::TranslateItem(this, 50910, "AITriggerMinDiff");
	Translations::TranslateItem(this, 50911, "AITriggerSide");
	Translations::TranslateItem(this, 50912, "AITriggerTechnoType");
	Translations::TranslateItem(this, 50913, "AITriggerCondition");
	Translations::TranslateItem(this, 50914, "AITriggerNumber");
	Translations::TranslateItem(this, 50915, "AITriggerAdditionalDesc");
	Translations::TranslateItem(this, 1210, "AITriggerData");

	Translations::TranslateItem(this, 1218, "AITriggerEnabled");
	Translations::TranslateItem(this, 1154, "AITriggerAdd");
	Translations::TranslateItem(this, 1066, "AITriggerDel");
	Translations::TranslateItem(this, 1919, "AITriggerClo");
	Translations::TranslateItem(this, 1452, "AITriggerBaseDefense");
	Translations::TranslateItem(this, 1453, "AITriggerSkirmish");
	Translations::TranslateItem(this, 1424, "AITriggerEasy");
	Translations::TranslateItem(this, 1425, "AITriggerMedium");
	Translations::TranslateItem(this, 1426, "AITriggerHard");

	HWND hSides;
	GetDlgItem(1456, &hSides);
	while (::SendMessage(hSides, CB_DELETESTRING, 0, NULL) != CB_ERR);

	::SendMessage(hSides, CB_ADDSTRING, NULL, (LPARAM)"0 - All");
	int i = 1;
	if (auto sides = CINI::FAData->GetSection("Sides"))
	{
		for (auto& itr : sides->EntitiesDictionary)
		{
			ppmfc::CString buffer;
			buffer.Format("%d - %s", i++, itr.second);
			::SendMessage(hSides, CB_ADDSTRING, NULL, (LPARAM)buffer.m_pchData);
		}
	}

	return TRUE;
}

BOOL CAITriggerTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_LBUTTONUP:
	{
		if (pMsg->hwnd == this->GetDlgItem(1919)->GetSafeHwnd())
			this->OnBNCloneAITriggerClicked();
	}
	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CAITriggerTypesExt::OnBNCloneAITriggerClicked()
{
	if (this->CCBAITriggerList.GetCount() > 0 && this->CCBAITriggerList.GetCurSel() != CB_ERR)
	{
		ppmfc::CString currentID;
		this->CCBAITriggerList.GetWindowText(currentID);
		STDHelpers::TrimIndex(currentID);

		ppmfc::CString key = CINI::GetAvailableIndex();
		ppmfc::CString value, name;

		HWND hName;
		GetDlgItem(1010, &hName);
		auto nLen = ::GetWindowTextLength(hName);
		auto pStr = new char[nLen + 1];
		::GetWindowText(hName, pStr, nLen + 1);
		name.Format("%s Clone", pStr);
		delete[] pStr;

		value = name + ",";
		auto& results = STDHelpers::SplitString(CINI::CurrentDocument->GetString("AITriggerTypes", currentID));
		for (int i = 1; i < results.size() - 1; ++i)
			value += (results[i] + ",");
		value += results.back();

		CINI::CurrentDocument->WriteString("AITriggerTypes", key, value);

		CINI::CurrentDocument->WriteString(
			"AITriggerTypesEnable", key,
			CINI::CurrentDocument->GetString("AITriggerTypesEnable", currentID, "no")
		);

		int idx = this->CCBAITriggerList.AddString(key + " (" + name + ")");
		this->CCBAITriggerList.SetCurSel(idx);

		this->SetDlgItemText(1010, name); // update the name huh
	}
}
