#include "Body.h"

#include <GlobalVars.h>
#include <CINI.h>

CurrentScript CScriptTypesExt::ExtCurrentScript;
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
		for (int i = index + 1; i < this->Count; ++i)
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
	auto& ini = GlobalVars::INIFiles::CurrentDocument();

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

void CurrentScript::Write(ppmfc::CString id, ppmfc::CString name)
{
	auto& ini = GlobalVars::INIFiles::CurrentDocument();

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