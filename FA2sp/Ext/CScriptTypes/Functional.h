#pragma once

#include "Body.h"

#include <GlobalVars.h>

#include <unordered_set>

void TrimIndex(CString& string) {
    string.TrimLeft();
    string.TrimRight();
    int spaceIndex = string.Find(' ');
    if (spaceIndex > 0)
        string = string.Mid(0, spaceIndex);
}

bool IsNullOrEmpty(const CString& string)
{
    int len = string.GetLength();
    if (len == 0)  return true;
    for (int i = 0; i < len; ++i)
        if (string[i] != ' ' && string[i] != '\0')  return false;
    return true;
}

// 1
void CScriptTypes_LoadParams_Target(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - Not specified"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Anything (uses auto-targeting)"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Buildings"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Harvesters"), 3);
    comboBox.SetItemData(comboBox.AddString("4 - Infantry"), 4);
    comboBox.SetItemData(comboBox.AddString("5 - Vehicles"), 5);
    comboBox.SetItemData(comboBox.AddString("6 - Factories"), 6);
    comboBox.SetItemData(comboBox.AddString("7 - Base defenses"), 7);
    comboBox.SetItemData(comboBox.AddString("9 - Power plants"), 9);
    comboBox.SetItemData(comboBox.AddString("10 - Occupiables"), 10);
    comboBox.SetItemData(comboBox.AddString("11 - Tech Buildings"), 11);
}

// 2
void CScriptTypes_LoadParams_Waypoint(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    int waypoints[702];
    memset(waypoints, -1, sizeof waypoints);
    if (doc.SectionExists("Waypoints"))
    {
        auto& entries = doc.GetSection("Waypoints");
        for (auto& x : entries.EntitiesDictionary)
        {
            if (x.first != "Name" && !IsNullOrEmpty(x.second))
            {
                int l = atoi(x.first);
                if (l <= 701 && l >= 0)
                    waypoints[l] = atoi(x.second);
            }
        }
    }
    char buffer[0x20];
    for (int i = 0; i < 702; ++i)
    {
        if (waypoints[i] >= 0)
        {
            sprintf_s(buffer, "%u - (%u, %u)", 
                i, waypoints[i] / 1000, waypoints[i] % 1000);
            int idx = comboBox.AddString(buffer);
            comboBox.SetItemData(idx, i);
        }
    }
}

// 3
void CScriptTypes_LoadParams_ScriptLine(CComboBox& comboBox, int cnt)
{
    // up to 50
    if (cnt > 50)
        cnt = 50;

    while (comboBox.DeleteString(0) != -1);

    char buf[3];
    for (int i = 0; i < cnt; ++i)
    {
        _itoa_s(i, buf, 10);
        int idx = comboBox.AddString(buf);
        comboBox.SetItemData(idx, i);
    }
}

// 4
void CScriptTypes_LoadParams_SplitGroup(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);
    
    comboBox.SetItemData(comboBox.AddString("0 - Keep Transports, Keep Units"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Keep Transports, Lose Units"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Lose Transports, Keep Units"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Lose Transports, Lose Units"), 3);
}

// 5
void CScriptTypes_LoadParams_GlobalVariables(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& rules = GlobalVars::INIFiles::Rules();
    if (rules.SectionExists("VariableNames"))
    {
        auto& entities = rules.GetSection("VariableNames");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (x.first != "Name" && !IsNullOrEmpty(x.first))
            {
                int l = atoi(x.first);
                text.Format("%d - %s", l, x.second);
                comboBox.SetItemData(comboBox.AddString(text), l);
            }
        }
    }
}

// 6
void CScriptTypes_LoadParams_ScriptTypes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("ScriptTypes"))
    {
        CString text;
        auto& entries = doc.GetSection("ScriptTypes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text = doc.GetString(ent.second, "Name");
                text.Format("%d - %s - %s", id, ent.second, text);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }

}

// 7
void CScriptTypes_LoadParams_TeamTypes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("TeamTypes"))
    {
        CString text;
        auto& entries = doc.GetSection("TeamTypes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text = doc.GetString(ent.second, "Name");
                text.Format("%d - %s - %s", id, ent.second, text);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }

}

// 8
void CScriptTypes_LoadParams_Houses(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("Houses"))
    {
        CString text;
        auto& entries = doc.GetSection("Houses");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 9
void CScriptTypes_LoadParams_Speechs(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& eva = GlobalVars::INIFiles::Eva();
    if (eva.SectionExists("DialogList"))
    {
        CString text;
        auto& entries = eva.GetSection("DialogList");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (eva.SectionExists(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s - %s", id, ent.second, eva.GetString(ent.second, "Text"));
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 10
void CScriptTypes_LoadParams_Sounds(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& sound = GlobalVars::INIFiles::Sound();
    if (sound.SectionExists("SoundList"))
    {
        CString text;
        auto& entries = sound.GetSection("SoundList");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (sound.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 11
void CScriptTypes_LoadParams_Movies(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& art = GlobalVars::INIFiles::Art();
    if (art.SectionExists("Movies"))
    {
        CString text;
        auto& entries = art.GetSection("Movies");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (ent.first != "Name")
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 12
void CScriptTypes_LoadParams_Themes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& theme = GlobalVars::INIFiles::Theme();
    if (theme.SectionExists("Themes"))
    {
        CString text;
        auto& entries = theme.GetSection("Themes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (theme.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 13
void CScriptTypes_LoadParams_Countries(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("Countries"))
    {
        CString text;
        auto& entries = doc.GetSection("Countries");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 14
void CScriptTypes_LoadParams_LocalVariables(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("VariableNames"))
    {
        auto& entities = doc.GetSection("VariableNames");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (IsNullOrEmpty(x.first) || x.first == "Name")
                continue;
            int l = atoi(x.first);
            text.Format("%d - %s", l, x.second);
            comboBox.SetItemData(comboBox.AddString(text), l);
        }
    }
}

// 15
void CScriptTypes_LoadParams_Facing(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - North"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - North East"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - East"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - South East"), 3);
    comboBox.SetItemData(comboBox.AddString("4 - South"), 4);
    comboBox.SetItemData(comboBox.AddString("5 - South West"), 5);
    comboBox.SetItemData(comboBox.AddString("6 - West"), 6);
    comboBox.SetItemData(comboBox.AddString("7 - North West"), 7);
}

// 16
void CScriptTypes_LoadParams_BuildingTypes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    std::unordered_set<int> HashSet;

    auto& rules = GlobalVars::INIFiles::Rules();
    if (rules.SectionExists("BuildingTypes"))
    {
        auto& entities = rules.GetSection("BuildingTypes");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (rules.SectionExists(x.second) && !IsNullOrEmpty(x.second))
            {
                int l = atoi(x.first);
                HashSet.insert(l);
                text.Format("%d - %s - %s", l, x.second, CSFQuery::GetUIName(x.second));
                comboBox.SetItemData(comboBox.AddString(text), l);
            }
        }
    }

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("BuildingTypes"))
    {
        auto& entities = doc.GetSection("BuildingTypes");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (rules.SectionExists(x.second) && doc.SectionExists(x.second) && !IsNullOrEmpty(x.second))
            {
                int l = atoi(x.first);
                text.Format("%d - %s - %s", l, x.second, CSFQuery::GetUIName(x.second));
                if (HashSet.find(l) != HashSet.end())
                {
                    comboBox.DeleteString(l);
                    comboBox.InsertString(l, text);
                    comboBox.SetItemData(l, l);
                }
                else
                    comboBox.SetItemData(comboBox.AddString(text), l);
            }
        }
    }
}

// 17
void CScriptTypes_LoadParams_Animations(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& rules = GlobalVars::INIFiles::Rules();
    if (rules.SectionExists("Animations"))
    {
        auto& entities = rules.GetSection("Animations");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (x.first != "Name" && !IsNullOrEmpty(x.first))
            {
                int l = atoi(x.first);
                text.Format("%d - %s", l, x.second);
                comboBox.SetItemData(comboBox.AddString(text), l);
            }
        }
    }
}

// 18
void CScriptTypes_LoadParams_TalkBubble(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - None"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Asterisk(*)"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Question mark(?)"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Exclamation mark(!)"), 3);
}

// 19
void CScriptTypes_LoadParams_Status(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    const char* pStatus[] =
    {
        "Sleep",
        "Attack nearest enemy",
        "Move",
        "QMove",
        "Retreat home for R&R",
        "Guard",
        "Sticky (never recruit)",
        "Enter object",
        "Capture object",
        "Move into & get eaten",
        "Harvest",
        "Area Guard",
        "Return (to refinery)",
        "Stop",
        "Ambush (wait until discovered)",
        "Hunt",
        "Unload",
        "Sabotage (move in & destroy)",
        "Construction",
        "Deconstruction",
        "Repair",
        "Rescue",
        "Missile",
        "Harmless",
        "Open",
        "Patrol",
        "Paradrop approach drop zone",
        "Paradrop overlay drop zone",
        "Wait",
        "Attack again",
        "Spyplane approach",
        "Spyplane overfly"
    };

    for (int i = 0; i < 32; ++i)
    {
        char buffer[0x40];
        sprintf_s(buffer, "%u - %s", i, pStatus[i]);
        int idx = comboBox.AddString(buffer);
        if (idx >= 0)
            comboBox.SetItemData(idx, i);
    }
}

// 20
void CScriptTypes_LoadParams_Boolean(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - FALSE"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - TRUE"), 1);
}