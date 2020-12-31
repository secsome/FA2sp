#pragma once

#include "Body.h"

#include <GlobalVars.h>

#include <unordered_set>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/ControlHelpers.h"

class CScriptTypesFunctions
{
public:

// 1
static void CScriptTypes_LoadParams_Target(CComboBox& comboBox)
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
static void CScriptTypes_LoadParams_Waypoint(CComboBox& comboBox)
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
            if (x.first != "Name" && !STDHelpers::IsNullOrEmpty(x.second))
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
                i, waypoints[i] % 1000, waypoints[i] / 1000);
            int idx = comboBox.AddString(buffer);
            comboBox.SetItemData(idx, i);
        }
    }
}

// 3
static void CScriptTypes_LoadParams_ScriptLine(CComboBox& comboBox, int cnt)
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
static void CScriptTypes_LoadParams_SplitGroup(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);
    
    comboBox.SetItemData(comboBox.AddString("0 - Keep Transports, Keep Units"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Keep Transports, Lose Units"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Lose Transports, Keep Units"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Lose Transports, Lose Units"), 3);
}

// 5
static void CScriptTypes_LoadParams_GlobalVariables(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& rules = GlobalVars::INIFiles::Rules();
    if (rules.SectionExists("VariableNames"))
    {
        auto& entities = rules.GetSection("VariableNames");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (x.first != "Name" && !STDHelpers::IsNullOrEmpty(x.first))
            {
                int l = atoi(x.first);
                text.Format("%d - %s", l, x.second);
                comboBox.SetItemData(comboBox.AddString(text), l);
            }
        }
    }
}

// 6
static void CScriptTypes_LoadParams_ScriptTypes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("ScriptTypes"))
    {
        CString text;
        auto& entries = doc.GetSection("ScriptTypes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
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
static void CScriptTypes_LoadParams_TeamTypes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("TeamTypes"))
    {
        CString text;
        auto& entries = doc.GetSection("TeamTypes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (doc.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
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
static void CScriptTypes_LoadParams_Houses(CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadHouses(comboBox, true);
}

// 9
static void CScriptTypes_LoadParams_Speechs(CComboBox& comboBox)
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
static void CScriptTypes_LoadParams_Sounds(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& sound = GlobalVars::INIFiles::Sound();
    if (sound.SectionExists("SoundList"))
    {
        CString text;
        auto& entries = sound.GetSection("SoundList");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (sound.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 11
static void CScriptTypes_LoadParams_Movies(CComboBox& comboBox)
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
static void CScriptTypes_LoadParams_Themes(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& theme = GlobalVars::INIFiles::Theme();
    if (theme.SectionExists("Themes"))
    {
        CString text;
        auto& entries = theme.GetSection("Themes");
        for (auto& ent : entries.EntitiesDictionary)
        {
            if (theme.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text.Format("%d - %s", id, ent.second);
                comboBox.SetItemData(comboBox.AddString(text), id);
            }
        }
    }
}

// 13
static void CScriptTypes_LoadParams_Countries(CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadCountries(comboBox, true);
}

// 14
static void CScriptTypes_LoadParams_LocalVariables(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    if (doc.SectionExists("VariableNames"))
    {
        auto& entities = doc.GetSection("VariableNames");
        CString text;
        for (auto& x : entities.EntitiesDictionary)
        {
            if (STDHelpers::IsNullOrEmpty(x.first) || x.first == "Name")
                continue;
            int l = atoi(x.first);
            text.Format("%d - %s", l, x.second);
            comboBox.SetItemData(comboBox.AddString(text), l);
        }
    }
}

// 15
static void CScriptTypes_LoadParams_Facing(CComboBox& comboBox)
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
static void CScriptTypes_LoadParams_BuildingTypes(CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadGenericList(comboBox, "BuildingTypes", true, true);
}

// 17
static void CScriptTypes_LoadParams_Animations(CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadGenericList(comboBox, "Animations", true, true);
}

// 18
static void CScriptTypes_LoadParams_TalkBubble(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - None"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Asterisk(*)"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Question mark(?)"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Exclamation mark(!)"), 3);
}

// 19
static void CScriptTypes_LoadParams_Status(CComboBox& comboBox)
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
static void CScriptTypes_LoadParams_Boolean(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    comboBox.SetItemData(comboBox.AddString("0 - FALSE"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - TRUE"), 1);
}

};