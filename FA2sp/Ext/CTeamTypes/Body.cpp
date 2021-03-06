#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTeamTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596D00 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596D30 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // veteran update
	RunTime::ResetMemoryContentAt(0x596D48 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // house update
	RunTime::ResetMemoryContentAt(0x596D60 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // priority update
	RunTime::ResetMemoryContentAt(0x596D78 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // max update
	RunTime::ResetMemoryContentAt(0x596D90 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // techlevel update
	RunTime::ResetMemoryContentAt(0x596DA8 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // group update
	RunTime::ResetMemoryContentAt(0x596DC0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // waypoint update
	RunTime::ResetMemoryContentAt(0x596DD8 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // script update
	RunTime::ResetMemoryContentAt(0x596DF0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // taskforce update
	RunTime::ResetMemoryContentAt(0x5970C0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // tag update
	RunTime::ResetMemoryContentAt(0x5970F0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // transport waypoint update
	RunTime::ResetMemoryContentAt(0x597120 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // mind control decision update

	RunTime::ResetMemoryContentAt(0x5971F8, &CTeamTypesExt::PreTranslateMessageExt);
	RunTime::ResetMemoryContentAt(0x597224, &CTeamTypesExt::OnInitDialogExt);
}

BOOL CTeamTypesExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->GetDlgItem(6001)->GetSafeHwnd())
			this->OnBNCloneClicked();
	}

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

BOOL CTeamTypesExt::OnInitDialogExt()
{
	BOOL ret = this->CTeamTypes::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, "TeamTypesTitle");

	Translations::TranslateItem(this, 1110, "TeamTypesNewTeam");
	Translations::TranslateItem(this, 1111, "TeamTypesDelTeam");
	Translations::TranslateItem(this, 6001, "TeamTypesCloTeam");

	Translations::TranslateItem(this, 50200, "TeamTypesMainDesc");
	Translations::TranslateItem(this, 50201, "TeamTypesCurrentTeamLabel");
	Translations::TranslateItem(this, 50202, "TeamTypesSelectedTeam");

	Translations::TranslateItem(this, 50203, "TeamTypesLabelName");
	Translations::TranslateItem(this, 50204, "TeamTypesLabelHouse");
	Translations::TranslateItem(this, 50205, "TeamTypesLabelTaskforce");
	Translations::TranslateItem(this, 50206, "TeamTypesLabelScript");
	Translations::TranslateItem(this, 50207, "TeamTypesLabelTag");
	Translations::TranslateItem(this, 50208, "TeamTypesLabelVeteranLevel");
	Translations::TranslateItem(this, 50209, "TeamTypesLabelPriority");
	Translations::TranslateItem(this, 50210, "TeamTypesLabelMax");
	Translations::TranslateItem(this, 50211, "TeamTypesLabelTechlevel");
	Translations::TranslateItem(this, 1413 , "TeamTypesLabelTransportWaypoint");
	Translations::TranslateItem(this, 50212, "TeamTypesLabelGroup");
	Translations::TranslateItem(this, 50213, "TeamTypesLabelWaypoint");

	Translations::TranslateItem(&this->CSTMindControlDecision, "TeamTypesLabelMindControlDecision");
	
	Translations::TranslateItem(this, 1113, "TeamTypesCheckBoxLoadable");
	Translations::TranslateItem(this, 1114, "TeamTypesCheckBoxFull");
	Translations::TranslateItem(this, 1115, "TeamTypesCheckBoxAnnoyance");
	Translations::TranslateItem(this, 1116, "TeamTypesCheckBoxGuardSlower");
	Translations::TranslateItem(this, 1117, "TeamTypesCheckBoxRecruiter");
	Translations::TranslateItem(this, 1119, "TeamTypesCheckBoxAutoCreate");
	Translations::TranslateItem(this, 1120, "TeamTypesCheckBoxPrebuild");
	Translations::TranslateItem(this, 1127, "TeamTypesCheckBoxReinforce");
	Translations::TranslateItem(this, 1128, "TeamTypesCheckBoxCargoPlane");
	Translations::TranslateItem(this, 1129, "TeamTypesCheckBoxWhiner");
	Translations::TranslateItem(this, 1130, "TeamTypesCheckBoxLooseRecruit");
	Translations::TranslateItem(this, 1131, "TeamTypesCheckBoxAggressive");
	Translations::TranslateItem(this, 1132, "TeamTypesCheckBoxSuicide");
	Translations::TranslateItem(this, 1133, "TeamTypesCheckBoxOnTransOnly");
	Translations::TranslateItem(this, 1134, "TeamTypesCheckBoxAvoidThreats");
	Translations::TranslateItem(this, 1135, "TeamTypesCheckBoxIonImmune");
	Translations::TranslateItem(this, 1136, "TeamTypesCheckBoxTransportsReturnOnUnload");
	Translations::TranslateItem(this, 1137, "TeamTypesCheckBoxAreTeamMembersRecruitable");
	Translations::TranslateItem(this, 1138, "TeamTypesCheckBoxIsBaseDefense");
	Translations::TranslateItem(this, 1139, "TeamTypesCheckBoxOnlyTargetHouseEnemy"); 

	return TRUE;
}

void CTeamTypesExt::OnBNCloneClicked()
{
	if (this->CCBTeamList.GetCount() > 0 && this->CCBTeamList.GetCurSel() >= 0)
	{
		int EditsID[13] = { 1010,1011,1012,1122,1143,1123,1126,1103,1140,1079,1124,1125,1083 };
		CWnd* Edits[13];
		for (int i = 0; i < 13; ++i)
			Edits[i] = GetDlgItem(EditsID[i]);
		int CheckID[20] = { 1113,1114,1115,1116,1117,1128,1129,1130,1131,1132,1119,1120,1127,1133,1134,1135,1137,1136,1138,1139 };
		CWnd* Check[20];
		for (int i = 0; i < 20; ++i)
			Check[i] = GetDlgItem(CheckID[i]);
		CString CurrentTeamData[13];
		for (int i = 0; i < 13; ++i)
			Edits[i]->GetWindowText(CurrentTeamData[i]);
		CurrentTeamData[0] += " Clone";
		int IsChecked[20];
		for (int i = 0; i < 20; ++i)
			IsChecked[i] = Check[i]->SendMessage(BM_GETCHECK, 0, 0);

		this->OnBNNewTeamClicked();

		for (int i = 0; i < 3; ++i)
		{
			Edits[i]->SetWindowText(CurrentTeamData[i]);
			this->SendMessage(WM_COMMAND, MAKEWPARAM(EditsID[i], EN_SETFOCUS), (LPARAM)Edits[i]->GetSafeHwnd());
			this->SendMessage(WM_COMMAND, MAKEWPARAM(EditsID[i], EN_KILLFOCUS), (LPARAM)Edits[i]->GetSafeHwnd());
		}
		for (int i = 3; i < 13; ++i)
		{
			Edits[i]->SetWindowText(CurrentTeamData[i]);
			this->SendMessage(WM_COMMAND, MAKEWPARAM(EditsID[i], CBN_SETFOCUS), (LPARAM)Edits[i]->GetSafeHwnd());
			this->SendMessage(WM_COMMAND, MAKEWPARAM(EditsID[i], CBN_KILLFOCUS), (LPARAM)Edits[i]->GetSafeHwnd());
		}

		for (int i = 0; i < 20; ++i)
		{
			Check[i]->SendMessage(BM_SETCHECK, IsChecked[i], 0);
			Check[i]->SendMessage(WM_LBUTTONDOWN, CheckID[i], 0);
			Check[i]->SendMessage(WM_LBUTTONUP, CheckID[i], 0);
			Check[i]->SendMessage(WM_LBUTTONDOWN, CheckID[i], 0);
			Check[i]->SendMessage(WM_LBUTTONUP, CheckID[i], 0);
		}

		for (int i = 0; i < 13; ++i)
			SAFE_RELEASE(Edits[i]);

		for (int i = 0; i < 20; ++i)
			SAFE_RELEASE(Check[i]);
	}

	/*
	CString src;
		this->CCBTeamList.GetWindowText(src);
		STDHelpers::TrimIndex(src);
		this->OnBNNewTeamClicked();
		CString des;
		this->CCBTeamList.GetWindowText(des);
		STDHelpers::TrimIndex(des);

		auto& doc = GlobalVars::INIFiles::CurrentDocument();

		FAString::Assignment(this->CString_Max, doc.GetString(src, "Max"));
		this->BOOL_Full = doc.GetBool(src, "Full");
		FAString::Assignment(this->CString_Name, doc.GetString(src, "Name") + " Clone");
		FAString::Assignment(this->CString_Group, doc.GetString(src, "Group"));
		FAString::Assignment(this->CString_House, doc.GetString(src, "House"));
		FAString::Assignment(this->CString_Script, doc.GetString(src, "Script"));
		this->BOOL_Whiner = doc.GetBool(src, "Whiner");
		// dropped
		this->BOOL_Suicide = doc.GetBool(src, "Suicide");
		this->BOOL_Loadable = doc.GetBool(src, "Loadable");
		this->BOOL_Prebuild = doc.GetBool(src, "Prebuild");
		FAString::Assignment(this->CString_Priority , doc.GetString(src, "Priority"));
		FAString::Assignment(this->CString_Waypoint , doc.GetString(src, "Waypoint"));
		this->BOOL_Annoyance = doc.GetBool(src, "Annoyance");
		this->BOOL_IonImmune = doc.GetBool(src, "IonImmune");
		this->BOOL_Recruiter = doc.GetBool(src, "Recruiter");
		this->BOOL_Reinforce = doc.GetBool(src, "Reinforce");
		FAString::Assignment(this->CString_Taskforce , doc.GetString(src, "TaskForce"));
		FAString::Assignment(this->CString_TechLevel , doc.GetString(src, "TechLevel"));
		this->BOOL_Aggressive = doc.GetBool(src, "Aggresive");
		this->BOOL_Autocreate = doc.GetBool(src, "Autocreate");
		this->BOOL_GuardSlower = doc.GetBool(src, "GuardSlower");
		this->BOOL_OnTransOnly = doc.GetBool(src, "OnTransOnly");
		this->BOOL_AvoidThreats = doc.GetBool(src, "AvoidThreats");
		this->BOOL_LooseRecruit = doc.GetBool(src, "LooseRecruit");
		FAString::Assignment(this->CString_VeteranLevel, doc.GetString(src, "VeteranLevel"));
		this->BOOL_IsBaseDefense = doc.GetBool(src, "IsBaseDefense");
		FAString::Assignment(this->CString_TransportWaypoint, doc.GetString(src, "TransportWaypoint"));
		// UseTransportOrigin
		FAString::Assignment(this->CString_MindControlDecision, doc.GetString(src, "MindControlDecision"));
		this->BOOL_OnlyTargetHouseEnemy = doc.GetBool(src, "OnlyTargetHouseEnemy");
		this->BOOL_TransportsReturnOnUnload = doc.GetBool(src, "TransportsReturnOnUnload");
		this->BOOL_AreTeamMembersRecruitable = doc.GetBool(src, "AreTeamMembersRecruitable");
		
		
		
		this->FA2CDialog::UpdateData(FALSE);*/
}