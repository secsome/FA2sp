#pragma once

#include "Body.h"

#include <CFinalSunDlg.h>

#include <unordered_set>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/ControlHelpers.h"
#include "../../FA2sp.h"

class CScriptTypesFunctions
{
public:

// negative
static void CScriptTypes_LoadParams_TypeList(ppmfc::CComboBox& comboBox, int nID)
{
    comboBox.DeleteAllStrings();

    ppmfc::CString buffer;
    buffer.Format("%d", nID);

    buffer = CINI::FAData->GetString("ScriptTypeLists", buffer);
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
            for (auto& pair : pSection->GetEntities())
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

// 1
static void CScriptTypes_LoadParams_Target(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

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
static void CScriptTypes_LoadParams_Waypoint(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& doc = CINI::CurrentDocument();
    
    if (!ExtConfigs::ExtWaypoints)
    {
        int waypoints[702];
        memset(waypoints, -1, sizeof waypoints);
        if (auto entries = doc.GetSection("Waypoints"))
            for (auto& x : entries->GetEntities())
                if (x.first != "Name" && !STDHelpers::IsNullOrEmpty(x.second))
                {
                    int l = atoi(x.first);
                    if (l <= 701 && l >= 0)
                        waypoints[l] = atoi(x.second);
                }
        char buffer[0x20];
        for (int i = 0; i < 702; ++i)
        {
            if (waypoints[i] >= 0)
            {
                sprintf_s(buffer, "%u - (%u, %u)", i, waypoints[i] % 1000, waypoints[i] / 1000);
                int idx = comboBox.AddString(buffer);
                comboBox.SetItemData(idx, i);
            }
        }
    }
    else
    {
        std::map<int, int> waypoints;
        if (auto entries = doc.GetSection("Waypoints"))
            for (auto& x : entries->GetEntities())
                if (x.first != "Name" && !STDHelpers::IsNullOrEmpty(x.second))
                {
                    int l = atoi(x.first);
                    if (l >= 0)
                        waypoints[l] = atoi(x.second);
                }
        ppmfc::CString buffer;
        for (auto& pair : waypoints)
        {
            if (pair.second >= 0)
            {
                buffer.Format("%u - (%u, %u)", pair.first, pair.second % 1000, pair.second / 1000);
                comboBox.SetItemData(comboBox.AddString(buffer), pair.first);
            }
        }
    }
    
}

// 3
static void CScriptTypes_LoadParams_ScriptLine(ppmfc::CComboBox& comboBox, ppmfc::CComboBox& currentScript, ppmfc::CListBox& listBox)
{
    int cnt = listBox.GetCount();
    // up to 50
    if (cnt > 50)
        cnt = 50;

    comboBox.DeleteAllStrings();

    auto& doc = CINI::CurrentDocument();

    ppmfc::CString buffer, scriptName, parambuf;
    currentScript.GetLBText(currentScript.GetCurSel(), scriptName);
    STDHelpers::TrimIndex(scriptName);

    for (int i = 0; i < cnt; ++i)
    {
        buffer.Format("%d", i);
        buffer = doc.GetString(scriptName, buffer, "0,0");
        int actionIndex = buffer.Find(',');
        if (actionIndex == CB_ERR)
            actionIndex = -1;
        else
            actionIndex = atoi(buffer.Mid(0, actionIndex));
        buffer.Format("%d - %s", i + 1, CScriptTypeAction::ExtActions[actionIndex].Name_);
        int idx = comboBox.AddString(buffer);
        comboBox.SetItemData(idx, i);
    }
}

// 4
static void CScriptTypes_LoadParams_SplitGroup(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();
    
    comboBox.SetItemData(comboBox.AddString("0 - Keep Transports, Keep Units"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Keep Transports, Lose Units"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Lose Transports, Keep Units"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Lose Transports, Lose Units"), 3);
}

// 5
static void CScriptTypes_LoadParams_GlobalVariables(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& rules = CINI::Rules();
    if (auto entities = rules.GetSection("VariableNames"))
    {
        CString text;
        for (auto& x : entities->GetEntities())
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
static void CScriptTypes_LoadParams_ScriptTypes(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& doc = CINI::CurrentDocument();
    if (auto entities = doc.GetSection("ScriptTypes"))
    {
        CString text, finaltext = "";
        for (auto& ent : entities->GetEntities())
        {
            if (doc.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text = doc.GetString(ent.second, "Name");
                finaltext.Format("%d - %s - %s", id, ent.second, text);
                comboBox.SetItemData(comboBox.AddString(finaltext), id);
            }
        }
    }

}

// 7
static void CScriptTypes_LoadParams_TeamTypes(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& doc = CINI::CurrentDocument();
    if (auto entities = doc.GetSection("TeamTypes"))
    {
        CString text, finaltext = "";
        for (auto& ent : entities->GetEntities())
        {
            if (doc.SectionExists(ent.second) && !STDHelpers::IsNullOrEmpty(ent.second))
            {
                int id = atoi(ent.first);
                text = doc.GetString(ent.second, "Name");
                finaltext.Format("%d - %s - %s", id, ent.second, text);
                comboBox.SetItemData(comboBox.AddString(finaltext), id);
            }
        }
    }

}

// 8
static void CScriptTypes_LoadParams_Houses(ppmfc::CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadHouses(comboBox, true);
}

// 9
static void CScriptTypes_LoadParams_Speechs(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& eva = CINI::Eva();
    if (auto entities = eva.GetSection("DialogList"))
    {
        CString text;
        for (auto& ent : entities->GetEntities())
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
static void CScriptTypes_LoadParams_Sounds(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& sound = CINI::Sound();
    if (auto entities = sound.GetSection("SoundList"))
    {
        CString text;
        for (auto& ent : entities->GetEntities())
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
static void CScriptTypes_LoadParams_Movies(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& art = CINI::Art();
    if (auto entities = art.GetSection("Movies"))
    {
        CString text;
        for (auto& ent : entities->GetEntities())
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
static void CScriptTypes_LoadParams_Themes(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& theme = CINI::Theme();
    if (auto entities = theme.GetSection("Themes"))
    {
        CString text;
        for (auto& ent : entities->GetEntities())
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
static void CScriptTypes_LoadParams_Countries(ppmfc::CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadCountries(comboBox, true);
}

// 14
static void CScriptTypes_LoadParams_LocalVariables(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    auto& doc = CINI::CurrentDocument();
    if (auto entities = doc.GetSection("VariableNames"))
    {
        CString text;
        for (auto& x : entities->GetEntities())
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
static void CScriptTypes_LoadParams_Facing(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    comboBox.SetItemData(comboBox.AddString("0 - NE"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - E"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - SE"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - S"), 3);
    comboBox.SetItemData(comboBox.AddString("4 - SW"), 4);
    comboBox.SetItemData(comboBox.AddString("5 - W"), 5);
    comboBox.SetItemData(comboBox.AddString("6 - NW"), 6);
    comboBox.SetItemData(comboBox.AddString("7 - N"), 7);
}

// 16
static void CScriptTypes_LoadParams_BuildingTypes(ppmfc::CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadGenericList(comboBox, "BuildingTypes", true, true);
}

// 17
static void CScriptTypes_LoadParams_Animations(ppmfc::CComboBox& comboBox)
{
    ControlHelpers::ComboBox::LoadGenericList(comboBox, "Animations", true, true);
}

// 18
static void CScriptTypes_LoadParams_TalkBubble(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    comboBox.SetItemData(comboBox.AddString("0 - None"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - Asterisk(*)"), 1);
    comboBox.SetItemData(comboBox.AddString("2 - Question mark(?)"), 2);
    comboBox.SetItemData(comboBox.AddString("3 - Exclamation mark(!)"), 3);
}

// 19
static void CScriptTypes_LoadParams_Status(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    int i = 0;
    comboBox.SetItemData(comboBox.AddString("0 - Sleep"), i++);
    comboBox.SetItemData(comboBox.AddString("1 - Attack nearest enemy"), i++);
    comboBox.SetItemData(comboBox.AddString("2 - Move"), i++);
    comboBox.SetItemData(comboBox.AddString("3 - QMove"), i++);
    comboBox.SetItemData(comboBox.AddString("4 - Retreat home for R&R"), i++);
    comboBox.SetItemData(comboBox.AddString("5 - Guard"), i++);
    comboBox.SetItemData(comboBox.AddString("6 - Sticky (never recruit)"), i++);
    comboBox.SetItemData(comboBox.AddString("7 - Enter object"), i++);
    comboBox.SetItemData(comboBox.AddString("8 - Capture object"), i++);
    comboBox.SetItemData(comboBox.AddString("9 - Move into & get eaten"), i++);
    comboBox.SetItemData(comboBox.AddString("10 - Harvest"), i++);
    comboBox.SetItemData(comboBox.AddString("11 - Area Guard"), i++);
    comboBox.SetItemData(comboBox.AddString("12 - Return (to refinery)"), i++);
    comboBox.SetItemData(comboBox.AddString("13 - Stop"), i++);
    comboBox.SetItemData(comboBox.AddString("14 - Ambush (wait until discovered)"), i++);
    comboBox.SetItemData(comboBox.AddString("15 - Hunt"), i++);
    comboBox.SetItemData(comboBox.AddString("16 - Unload"), i++);
    comboBox.SetItemData(comboBox.AddString("17 - Sabotage (move in & destroy)"), i++);
    comboBox.SetItemData(comboBox.AddString("18 - Construction"), i++);
    comboBox.SetItemData(comboBox.AddString("19 - Deconstruction"), i++);
    comboBox.SetItemData(comboBox.AddString("20 - Repair"), i++);
    comboBox.SetItemData(comboBox.AddString("21 - Rescue"), i++);
    comboBox.SetItemData(comboBox.AddString("22 - Missile"), i++);
    comboBox.SetItemData(comboBox.AddString("23 - Harmless"), i++);
    comboBox.SetItemData(comboBox.AddString("24 - Open"), i++);
    comboBox.SetItemData(comboBox.AddString("25 - Patrol"), i++);
    comboBox.SetItemData(comboBox.AddString("26 - Paradrop approach drop zone"), i++);
    comboBox.SetItemData(comboBox.AddString("27 - Paradrop overlay drop zone"), i++);
    comboBox.SetItemData(comboBox.AddString("28 - Wait"), i++);
    comboBox.SetItemData(comboBox.AddString("29 - Attack again"), i++);
    comboBox.SetItemData(comboBox.AddString("30 - Spyplane approach"), i++);
    comboBox.SetItemData(comboBox.AddString("31 - Spyplane overfly"), i++);
}

// 20
static void CScriptTypes_LoadParams_Boolean(ppmfc::CComboBox& comboBox)
{
    comboBox.DeleteAllStrings();

    comboBox.SetItemData(comboBox.AddString("0 - FALSE"), 0);
    comboBox.SetItemData(comboBox.AddString("1 - TRUE"), 1);
}

};