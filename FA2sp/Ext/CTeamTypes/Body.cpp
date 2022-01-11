#include "Body.h"

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

	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
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
		ppmfc::CString currentID;
		this->CCBTeamList.GetWindowText(currentID);
		STDHelpers::TrimIndex(currentID);

		ppmfc::CString key = CINI::GetAvailableKey("TeamTypes");
		ppmfc::CString value = CINI::GetAvailableIndex();

		CINI::CurrentDocument->WriteString("TeamTypes", key, value);

		auto name = CINI::CurrentDocument->GetString(currentID, "Name", "New Teamtype") + " Clone";
		CINI::CurrentDocument->WriteString(value, "Name", name);

		auto copyitem = [&value, &currentID](ppmfc::CString key)
		{
			if (auto ppStr = CINI::CurrentDocument->TryGetString(currentID, key))
				CINI::CurrentDocument->WriteString(value, key, *ppStr);
		};

		copyitem("Max");
		copyitem("Full");
		copyitem("Group");
		copyitem("House");
		copyitem("Script");
		copyitem("Whiner");
		copyitem("Droppod");
		copyitem("Suicide");
		copyitem("Loadable");
		copyitem("Prebuild");
		copyitem("Priority");
		copyitem("Waypoint");
		copyitem("Annoyance");
		copyitem("IonImmune");
		copyitem("Recruiter");
		copyitem("Reinforce");
		copyitem("TaskForce");
		copyitem("TechLevel");
		copyitem("Aggressive");
		copyitem("Autocreate");
		copyitem("GuardSlower");
		copyitem("OnTransOnly");
		copyitem("AvoidThreats");
		copyitem("LooseRecruit");
		copyitem("VeteranLevel");
		copyitem("IsBaseDefense");
		copyitem("TransportWaypoint");
		copyitem("UseTransportOrigin");
		copyitem("MindControlDecision");
		copyitem("OnlyTargetHouseEnemy");
		copyitem("TransportsReturnOnUnload");
		copyitem("AreTeamMembersRecruitable");

		int idx = this->CCBTeamList.AddString(value + " (" + name + ")");
		this->CCBTeamList.SetCurSel(idx);

		// this->OnCBCurrentTaskforceSelectChanged(); unnecessary, this is not needed for we should display them same thing
		this->SetDlgItemText(1010, name); // update the name huh
	}
}