#include "Body.h"

#include <Helpers/Macro.h>

#include <CMapData.h>
#include <CLoading.h>

#include "../../Helpers/STDHelpers.h"

#include "../../FA2sp.h"

DEFINE_HOOK(4E7900, CTeamTypes_OnCBCurrentTeamSelectChanged, 7)
{
	GET(CTeamTypes*, pThis, ECX);
	auto pINI = CMapData::Instance->UpdateCurrentDocument();

	if (pThis->CCBTeamList.GetCurSel() >= 0)
	{
		ppmfc::CString ID = STDHelpers::GetComboBoxText(pThis->CCBTeamList);
		STDHelpers::TrimIndex(ID);
		if (pINI->SectionExists(ID))
		{
			pThis->BOOL_Aggressive = pINI->GetBool(ID, "Aggressive");
			pThis->BOOL_Annoyance = pINI->GetBool(ID, "Annoyance");
			pThis->BOOL_AreTeamMembersRecruitable = pINI->GetBool(ID, "AreTeamMembersRecruitable");
			pThis->BOOL_Autocreate = pINI->GetBool(ID, "Autocreate");
			pThis->BOOL_AvoidThreats = pINI->GetBool(ID, "AvoidThreats");
			pThis->BOOL_CargoPlane = pINI->GetBool(ID, "CargoPlane");
			pThis->BOOL_Full = pINI->GetBool(ID, "Full");
			pThis->BOOL_GuardSlower = pINI->GetBool(ID, "GuardSlower");
			pThis->BOOL_IonImmune = pINI->GetBool(ID, "IonImmune");
			pThis->BOOL_IsBaseDefense = pINI->GetBool(ID, "IsBaseDefense");
			pThis->BOOL_Loadable = pINI->GetBool(ID, "Loadable");
			pThis->BOOL_LooseRecruit = pINI->GetBool(ID, "LooseRecruit");
			pThis->BOOL_OnlyTargetHouseEnemy = pINI->GetBool(ID, "OnlyTargetHouseEnemy");
			pThis->BOOL_OnTransOnly = pINI->GetBool(ID, "OnTransOnly");
			pThis->BOOL_Prebuild = pINI->GetBool(ID, "Prebuild");
			pThis->BOOL_Recruiter = pINI->GetBool(ID, "Recruiter");
			pThis->BOOL_Reinforce = pINI->GetBool(ID, "Reinforce");
			pThis->BOOL_Suicide = pINI->GetBool(ID, "Suicide");
			pThis->BOOL_TransportsReturnOnUnload = pINI->GetBool(ID, "TransportsReturnOnUnload");
			pThis->BOOL_Whiner = pINI->GetBool(ID, "Whiner");
			pThis->CString_Group = pINI->GetString(ID, "Group");
			pThis->CString_House = pINI->GetString(ID, "House");
			pThis->CString_Max = pINI->GetString(ID, "Max");
			pThis->CString_Name = pINI->GetString(ID, "Name");
			pThis->CString_Priority = pINI->GetString(ID, "Priority");
			pThis->CString_TechLevel = pINI->GetString(ID, "TechLevel");

			pThis->CString_VeteranLevel = pINI->GetString(ID, "VeteranLevel");
			if (CLoading::HasMdFile)
				pThis->CString_MindControlDecision = pINI->GetString(ID, "MindControlDecision");

			pThis->CString_Waypoint.Format("%d", Waypoints::String_To_Waypoint(pINI->GetString(ID, "Waypoint")));
			if (auto ppStr = pINI->TryGetString(ID, "TransportWaypoint"))
				pThis->CString_TransportWaypoint.Format("%d", Waypoints::String_To_Waypoint(*ppStr));
			else
				pThis->CString_TransportWaypoint = "None";

			auto GetNamedString = [&](ppmfc::CString& des, const char* KeyName, const char* SectionName)
			{
				des = pINI->GetString(ID, KeyName);
				des += " (" + pINI->GetString(des, "Name") + ")";
			};

			GetNamedString(pThis->CString_Script, "Script", "ScriptTypes");
			GetNamedString(pThis->CString_TaskForce, "TaskForce", "TaskForces");
			
			if (auto ppStr = pINI->TryGetString(ID, "Tag"))
			{
				pThis->CString_Tag = *ppStr;
				auto tagcontent = STDHelpers::SplitString(pINI->GetString("Tags", ID));
				if (tagcontent.size() >= 2)
					pThis->CString_Tag += " (" + tagcontent[1] + ")";
			}
			else
				pThis->CString_Tag = "None";

			pThis->UpdateData(FALSE);
		}
	}

	return 0x4E9B11;
}