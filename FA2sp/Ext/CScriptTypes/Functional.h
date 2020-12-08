#pragma once

#include "Body.h"

#include <GlobalVars.h>

void TrimIndex(CString& string) {
    string.TrimLeft();
    string.TrimRight();
    int spaceIndex = string.Find(' ');
    if (spaceIndex > 0)
        string = string.Mid(0, spaceIndex);
}

// 1
void CScriptTypes_LoadParams_Target(CComboBox& comboBox)
{
    while (comboBox.DeleteString(0) != -1);

    auto addString = [&comboBox](const char* lpzStr, int data) {
        int idx = comboBox.AddString(lpzStr);
        if (idx >= 0)
            comboBox.SetItemData(idx, data);
    };

    addString("0 - Not specified", 0);
    addString("1 - Anything (uses auto-targeting)", 1);
    addString("2 - Buildings", 2);
    addString("3 - Harvesters", 3);
    addString("4 - Infantry", 4);
    addString("5 - Vehicles", 5);
    addString("6 - Factories", 6);
    addString("7 - Base defenses", 7);
    addString("9 - Power plants", 9);
    addString("10 - Occupiables", 10);
    addString("11 - Tech Buildings", 11);
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
        for (auto& x : entries.EntriesDictionary)
        {
            int l = atoi(x.first);
            if (l <= 701 && l >= 0)
                waypoints[l] = atoi(x.second);
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

//3
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
        for (auto& x : entities.EntriesDictionary)
        {
            int l = atoi(x.first);
            text.Format("%d - %s", l, x.second);
            comboBox.SetItemData(comboBox.AddString(text), l);
        }
    }
}

// 6
void CScriptTypes_LoadParams_ScriptTypes(CComboBox& comboBox, CComboBox& src)
{
    while (comboBox.DeleteString(0) != -1);

    int cnt = src.GetCount();
    for (int i = 0; i < cnt; ++i)
    {
        CString text;
        src.GetLBText(i, text);
        int idx = comboBox.AddString(text);
        TrimIndex(text);
        comboBox.SetItemData(idx, atoi(text));
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