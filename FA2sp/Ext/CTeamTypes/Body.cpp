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

	auto addr = &CTeamTypesExt::PreTranslateMessageExt;
	RunTime::ResetMemoryContentAt(0x5971F8, &addr, 4);
	auto addr2 = &CTeamTypesExt::OnInitDialogExt;
	RunTime::ResetMemoryContentAt(0x597224, &addr2, 4);
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

	auto TranslateDlgItem = [this](int nID, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			this->SetDlgItemText(nID, buffer);
	};

	auto TranslateCItem = [](CWnd* pWnd, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			pWnd->SetWindowText(buffer);
	};
	TranslateCItem(this, "TeamTypesTitle");

	TranslateDlgItem(1110, "TeamTypesNewTeam");
	TranslateDlgItem(1111, "TeamTypesDelTeam");
	TranslateDlgItem(6001, "TeamTypesCloTeam");

	TranslateDlgItem(50200, "TeamTypesMainDesc");
	TranslateDlgItem(50201, "TeamTypesCurrentTeamLabel");
	TranslateDlgItem(50202, "TeamTypesSelectedTeam");

	TranslateDlgItem(50203, "TeamTypesLabelName");
	TranslateDlgItem(50204, "TeamTypesLabelHouse");
	TranslateDlgItem(50205, "TeamTypesLabelTaskforce");
	TranslateDlgItem(50206, "TeamTypesLabelScript");
	TranslateDlgItem(50207, "TeamTypesLabelTag");
	TranslateDlgItem(50208, "TeamTypesLabelVeteranLevel");
	TranslateDlgItem(50209, "TeamTypesLabelPriority");
	TranslateDlgItem(50210, "TeamTypesLabelMax");
	TranslateDlgItem(50211, "TeamTypesLabelTechlevel");
	TranslateDlgItem(1413 , "TeamTypesLabelTransportWaypoint");
	TranslateDlgItem(50212, "TeamTypesLabelGroup");
	TranslateDlgItem(50213, "TeamTypesLabelWaypoint");

	TranslateCItem(&this->CSTMindControlDecision, "TeamTypesLabelMindControlDecision");
	
	TranslateDlgItem(1113, "TeamTypesCheckBoxLoadable");
	TranslateDlgItem(1114, "TeamTypesCheckBoxFull");
	TranslateDlgItem(1115, "TeamTypesCheckBoxAnnoyance");
	TranslateDlgItem(1116, "TeamTypesCheckBoxGuardSlower");
	TranslateDlgItem(1117, "TeamTypesCheckBoxRecruiter");
	TranslateDlgItem(1119, "TeamTypesCheckBoxAutoCreate");
	TranslateDlgItem(1120, "TeamTypesCheckBoxPrebuild");
	TranslateDlgItem(1127, "TeamTypesCheckBoxReinforce");
	TranslateDlgItem(1128, "TeamTypesCheckBoxCargoPlane");
	TranslateDlgItem(1129, "TeamTypesCheckBoxWhiner");
	TranslateDlgItem(1130, "TeamTypesCheckBoxLooseRecruit");
	TranslateDlgItem(1131, "TeamTypesCheckBoxAggressive");
	TranslateDlgItem(1132, "TeamTypesCheckBoxSuicide");
	TranslateDlgItem(1133, "TeamTypesCheckBoxOnTransOnly");
	TranslateDlgItem(1134, "TeamTypesCheckBoxAvoidThreats");
	TranslateDlgItem(1135, "TeamTypesCheckBoxIonImmune");
	TranslateDlgItem(1136, "TeamTypesCheckBoxTransportsReturnOnUnload");
	TranslateDlgItem(1137, "TeamTypesCheckBoxAreTeamMembersRecruitable");
	TranslateDlgItem(1138, "TeamTypesCheckBoxIsBaseDefense");
	TranslateDlgItem(1139, "TeamTypesCheckBoxOnlyTargetHouseEnemy"); 
	
	return TRUE;
}

void CTeamTypesExt::OnBNCloneClicked()
{
	::MessageBox(NULL, "还没实装，爬", "咕咕咕", MB_OK);
	return;
	if (this->CCBTeamList.GetCount() > 0 && this->CCBTeamList.GetCurSel() >= 0)
	{
		CString src;
		this->CCBTeamList.GetWindowText(src);
		STDHelpers::TrimIndex(src);
		this->OnBNNewTeamClicked();
		CString des;
		this->CCBTeamList.GetWindowText(des);
		STDHelpers::TrimIndex(des);

		auto& doc = GlobalVars::INIFiles::CurrentDocument();
		
		auto copy_team = [&doc, &src, &des](const char* pItem)
		{
			CString origin = doc.GetString(src, pItem);
			doc.WriteString(des, pItem, origin);
		};

		copy_team("Max");
		copy_team("Full");
		copy_team("Name");
		copy_team("Group");
		copy_team("House");
		copy_team("Script");
		copy_team("Whiner");
		copy_team("Droppod");
		copy_team("Suicide");
		copy_team("Loadable");
		copy_team("Prebuild");
		copy_team("Priority");
		copy_team("Waypoint");
		copy_team("Annoyance");
		copy_team("IonImmune");
		copy_team("Recruiter");
		copy_team("Reinforce");
		copy_team("TaskForce");
		copy_team("TechLevel");
		copy_team("Aggressive");
		copy_team("Autocreate");
		copy_team("GuardSlower");
		copy_team("OnTransOnly");
		copy_team("AvoidThreats");
		copy_team("LooseRecruit");
		copy_team("VeteranLevel");
		copy_team("IsBaseDefense");
		copy_team("TransportWaypoint");
		copy_team("UseTransportOrigin");
		copy_team("MindControlDecision");
		copy_team("OnlyTargetHouseEnemy");
		copy_team("TransportsReturnOnUnload");
		copy_team("AreTeamMembersRecruitable");

		doc.WriteString(des, "Name", 
			doc.GetString(src, "Name", "Clone Script") + " Clone");

		this->OnCBCurrentTeamSelectedChanged();
	}
}