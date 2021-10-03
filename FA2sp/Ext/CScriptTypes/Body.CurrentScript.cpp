#include "Body.h"
#include "Functional.h"

#include <CINI.h>
#include <CFinalSunDlg.h>

CurrentScript* CScriptTypesExt::ExtCurrentScript;
ppmfc::CString CurrentScript::ToString()
{
	return this->ID + " (" + this->Name + ")";
}

ppmfc::CString CurrentScript::GetActionString(int index)
{
	if (!this->Actions[index].IsEmpty())
	{
		auto& action = this->Actions[index];
		ppmfc::CString ret;
		ret.Format("%d,%d", action.Type, action.Param);
		return ret;
	}
	return "";
}

int CurrentScript::AddAction(ScriptNode& node)
{
	if (this->Count < 50)
	{
		this->Actions[Count++] = node;
		return this->Count;
	}
	return -1;
}

int CurrentScript::AddAction(int type, int param)
{
	ScriptNode buffer;
	buffer.Type = type;
	buffer.Param = param;
	return this->AddAction(buffer);
}

int CurrentScript::AddAction(int type, short param, short ext)
{
	ScriptNode buffer;
	buffer.Type = type;
	buffer.ParamNormal = param;
	buffer.ParamExt = ext;
	return this->AddAction(buffer);
}

bool CurrentScript::AddActionAt(ScriptNode& node, int index)
{
	if (this->Count < 50 && index < 50)
	{
		for (int i = Count; i > index; --i)
			this->Actions[i] = this->Actions[i - 1];

		this->Actions[index] = node;
		++this->Count;
		return true;
	}
	return false;
}

bool CurrentScript::AddActionAt(int type, int param, int index)
{
	ScriptNode buffer;
	buffer.Type = type;
	buffer.Param = param;
	return this->AddActionAt(buffer, index);
}

bool CurrentScript::AddActionAt(int type, short param, short ext, int index)
{
	ScriptNode buffer;
	buffer.Type = type;
	buffer.ParamNormal = param;
	buffer.ParamExt = ext;
	return this->AddActionAt(buffer, index);
}

int CurrentScript::GetActionCount()
{
	return this->Count;
}

CurrentScript::ScriptNode& CurrentScript::RemoveActionAt(int index)
{
	ScriptNode buffer = this->Actions[index];
	for (int i = index; i < this->Count - 1; ++i)
		this->Actions[i] = this->Actions[i + 1];
	this->Actions[this->Count].MakeEmpty();
	--this->Count;
	return buffer;
}

void CurrentScript::Set(ppmfc::CString id)
{
	auto& ini = CINI::CurrentDocument();

	if (auto const pSection = ini.GetSection(id))
	{
		ppmfc::CString key;
		int count = 0;
		for (int i = 0; i < 50; ++i)
		{
			key.Format("%d", i);
			auto itr = pSection->EntitiesDictionary.find(key);
			if (itr != pSection->EntitiesDictionary.end())
			{
				key = itr->second;
				if (sscanf_s(key, "%d,%d", &this->Actions[count].Type, &this->Actions[count].Param) == 2)
					++count;
			}
		}
		this->Count = count;
		this->Name = ini.GetString(id, "Name", "No name");
		this->ID = id;
	}
}

void CurrentScript::Unset()
{
	this->Count = -1;
	this->Name = "";
	this->ID = "";
}

bool CurrentScript::IsAvailable()
{
	return this->Count != -1;
}

void CurrentScript::Write(ppmfc::CString id, ppmfc::CString name)
{
	auto& ini = CINI::CurrentDocument();
	
	ini.DeleteSection(id);
	ini.WriteString(id, "Name", name);
	ppmfc::CString buffer;
	for (int i = 0; i < this->Count; ++i)
	{
		buffer.Format("%d", i);
		ini.WriteString(id, buffer, this->GetActionString(i));
	}
}

void CurrentScript::Write()
{
	this->Write(this->ID, this->Name);
}

void CurrentScript::WriteLine(ppmfc::CString id, int line)
{
	auto& ini = CINI::CurrentDocument();

	ppmfc::CString buffer;
	buffer.Format("%d", line);
	ini.WriteString(id, buffer, this->GetActionString(line));
}

void CurrentScript::WriteLine(int line)
{
	this->WriteLine(this->ID, line);
}

bool CurrentScript::IsExtraParamEnabled(int actionIndex)
{
	if (actionIndex == 46 || actionIndex == 47 || actionIndex == 56 || actionIndex == 58)
		return true;
	auto itr = CScriptTypeAction::ExtActions.find(actionIndex);
	if (itr == CScriptTypeAction::ExtActions.end())
		return false;
	const auto& param = CScriptTypeParam::ExtParams[itr->second.ParamCode_].Param_;
	if (param < 0)
	{
		ppmfc::CString buffer;
		buffer.Format("%d", -param);
		buffer = CINI::FAData->GetString("ScriptTypeLists", buffer);
		return CINI::FAData->GetBool(buffer, "HasExtraParam");
	}
	return false;
}

bool CurrentScript::IsExtraParamEnabledAtLine(int line)
{
	return this->IsExtraParamEnabled(this->Actions[line].Type);
}

void CurrentScript::LoadExtraParamBox(ppmfc::CComboBox& comboBox, int actionIndex)
{
	while (comboBox.DeleteString(0) != CB_ERR);

	if (actionIndex == 46 || actionIndex == 47 || actionIndex == 56 || actionIndex == 58)
	{
		comboBox.SetItemData(comboBox.AddString("0 - Min Threat"), 0);
		comboBox.SetItemData(comboBox.AddString("1 - Max Threat"), 1);
		comboBox.SetItemData(comboBox.AddString("2 - Nearest"), 2);
		comboBox.SetItemData(comboBox.AddString("3 - Farthest"), 3);
		return;
	}

	auto itr = CScriptTypeAction::ExtActions.find(actionIndex);
	if (itr == CScriptTypeAction::ExtActions.end())
		return;
	const auto& param = CScriptTypeParam::ExtParams[itr->second.ParamCode_].Param_;
	if (param < 0)
	{
		ppmfc::CString buffer;
		buffer.Format("%d", -param);

		buffer = CINI::FAData->GetString("ScriptTypeLists", buffer);
		if (CINI::FAData->GetBool(buffer, "HasExtraParam"))
		{
			buffer = CINI::FAData->GetString(buffer, "ExtraParamType");
			int nBuiltInType = CINI::FAData->GetInteger(buffer, "BuiltInType", -1);
			if (nBuiltInType != -1)
			{
				switch (nBuiltInType)
				{
				default:
				case 0:
					break;
				case 1:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Target(comboBox);
					break;
				case 2:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Waypoint(comboBox);
					break;
				case 3:
					CScriptTypesFunctions::CScriptTypes_LoadParams_ScriptLine(
						comboBox,
						CFinalSunDlg::Instance->ScriptTypes.CCBCurrentScript,
						CFinalSunDlg::Instance->ScriptTypes.CLBScriptActions
					);
					break;
				case 4:
					CScriptTypesFunctions::CScriptTypes_LoadParams_SplitGroup(comboBox);
					break;
				case 5:
					CScriptTypesFunctions::CScriptTypes_LoadParams_GlobalVariables(comboBox);
					break;
				case 6:
					CScriptTypesFunctions::CScriptTypes_LoadParams_ScriptTypes(comboBox);
					break;
				case 7:
					CScriptTypesFunctions::CScriptTypes_LoadParams_TeamTypes(comboBox);
					break;
				case 8:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Houses(comboBox);
					break;
				case 9:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Speechs(comboBox);
					break;
				case 10:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Sounds(comboBox);
					break;
				case 11:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Movies(comboBox);
					break;
				case 12:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Themes(comboBox);
					break;
				case 13:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Countries(comboBox);
					break;
				case 14:
					CScriptTypesFunctions::CScriptTypes_LoadParams_LocalVariables(comboBox);
					break;
				case 15:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Facing(comboBox);
					break;
				case 16:
					CScriptTypesFunctions::CScriptTypes_LoadParams_BuildingTypes(comboBox);
					break;
				case 17:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Animations(comboBox);
					break;
				case 18:
					CScriptTypesFunctions::CScriptTypes_LoadParams_TalkBubble(comboBox);
					break;
				case 19:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Status(comboBox);
					break;
				case 20:
					CScriptTypesFunctions::CScriptTypes_LoadParams_Boolean(comboBox);
					break;
				}
			}
			else
			{
				if (auto pSection = CINI::FAData->GetSection(buffer))
					for (auto& pair : pSection->EntitiesDictionary)
					{
						int data;
						if (sscanf_s(pair.first, "%d", &data) == 1)
						{
							buffer = pair.first + " - " + pair.second;
							comboBox.SetItemData(comboBox.AddString(buffer), data);
						}
					}
			}
		}
	}
}