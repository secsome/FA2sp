#include <Helpers/Macro.h>
#include <CMapData.h>

#include <map>

#include "../FA2sp.h"
#include "../Helpers/STDHelpers.h"
#include "../Helpers/ControlHelpers.h"

DEFINE_HOOK(43CE8D, Miscs_LoadParamToCombobox, 9)
{
    GET(ppmfc::CComboBox*, pComboBox, ESI);
    GET(int, nCode, EAX);

    if (nCode <= 30) // 30 is our float
        return 0;
    
    // Consistence with FA2Ext
    switch (nCode)
    {
    case 31: // Enter Status
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Sleep");
        pComboBox->AddString("1 - Attack nearest enemy");
        pComboBox->AddString("2 - Move");
        pComboBox->AddString("3 - QMove");
        pComboBox->AddString("4 - Retreat home for R&R");
        pComboBox->AddString("5 - Guard");
        pComboBox->AddString("6 - Sticky (never recruit)");
        pComboBox->AddString("7 - Enter object");
        pComboBox->AddString("8 - Capture object");
        pComboBox->AddString("9 - Move into & get eaten");
        pComboBox->AddString("10 - Harvest");
        pComboBox->AddString("11 - Area Guard");
        pComboBox->AddString("12 - Return (to refinery)");
        pComboBox->AddString("13 - Stop");
        pComboBox->AddString("14 - Ambush (wait until discovered)");
        pComboBox->AddString("15 - Hunt");
        pComboBox->AddString("16 - Unload");
        pComboBox->AddString("17 - Sabotage (move in & destroy)");
        pComboBox->AddString("18 - Construction");
        pComboBox->AddString("19 - Deconstruction");
        pComboBox->AddString("20 - Repair");
        pComboBox->AddString("21 - Rescue");
        pComboBox->AddString("22 - Missile");
        pComboBox->AddString("23 - Harmless");
        pComboBox->AddString("24 - Open");
        pComboBox->AddString("25 - Patrol");
        pComboBox->AddString("26 - Paradrop approach drop zone");
        pComboBox->AddString("27 - Paradrop overlay drop zone");
        pComboBox->AddString("28 - Wait");
        pComboBox->AddString("29 - Attack again");
        pComboBox->AddString("30 - Spyplane approach");
        pComboBox->AddString("31 - Spyplane overfly");
        break;
    case 32: // Targets
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Not specified");
        pComboBox->AddString("1 - Anything (uses auto-targeting)");
        pComboBox->AddString("2 - Buildings");
        pComboBox->AddString("3 - Harvesters");
        pComboBox->AddString("4 - Infantry");
        pComboBox->AddString("5 - Vehicles");
        pComboBox->AddString("6 - Factories");
        pComboBox->AddString("7 - Base defenses");
        pComboBox->AddString("9 - Power plants");
        pComboBox->AddString("10 - Occupiables");
        pComboBox->AddString("11 - Tech Buildings");
        break;
    case 33: // Facing
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - NE");
        pComboBox->AddString("1 - E");
        pComboBox->AddString("2 - SE");
        pComboBox->AddString("3 - S");
        pComboBox->AddString("4 - SW");
        pComboBox->AddString("5 - W");
        pComboBox->AddString("6 - NW");
        pComboBox->AddString("7 - N");
        break;
    case 34: // Split
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Keep Transports, Keep Units");
        pComboBox->AddString("1 - Keep Transports, Lose Units");
        pComboBox->AddString("2 - Lose Transports, Keep Units");
        pComboBox->AddString("3 - Lose Transports, Lose Units");
        break;
    case 35: // Camera Move Speed
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Very Slow");
        pComboBox->AddString("1 - Slow");
        pComboBox->AddString("2 - Normal");
        pComboBox->AddString("3 - Fast");
        pComboBox->AddString("4 - Very Fast");
        break;
    case 37: // Radar Event Type
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Combat");
        pComboBox->AddString("1 - Non Combat");
        pComboBox->AddString("2 - Drop Zone");
        pComboBox->AddString("3 - Base Attack");
        pComboBox->AddString("4 - Harvest Attack");
        pComboBox->AddString("5 - Enemy Sensed");
        pComboBox->AddString("6 - Unit Ready");
        pComboBox->AddString("7 - Unit Lost");
        pComboBox->AddString("8 - Unit Repaired");
        pComboBox->AddString("9 - Building Infiltrated");
        pComboBox->AddString("10 - Building Captured");
        pComboBox->AddString("11 - Beacon Placed");
        pComboBox->AddString("12 - SW Detected");
        pComboBox->AddString("13 - SW Activated");
        pComboBox->AddString("14 - Bridge Repaired");
        pComboBox->AddString("15 - Garrison Abandoned");
        pComboBox->AddString("16 - Ally Attack");
        break;
    case 38: // Tabpage
        pComboBox->DeleteAllStrings();
        pComboBox->AddString("0 - Buildings");
        pComboBox->AddString("1 - Defenses");
        pComboBox->AddString("2 - Infantries");
        pComboBox->AddString("3 - Units");
        break;
    case 39: // SuperWeaponTypes (ID)
        ControlHelpers::ComboBox::LoadGenericList(*pComboBox, "SuperWeaponTypes", true, true);
        break;
    default: // Not a valid param
        break;
    }

    return 0x43D037;
}

DEFINE_HOOK(43D037, Miscs_LoadParams_AdjustComboboxDropdownWidth, C)
{
    if (ExtConfigs::AdjustDropdownWidth)
    {
        GET_STACK(ppmfc::CComboBox*, pComboBox, STACK_OFFS(0x18, -0x4));

        int nWidth = 120;
        for (int i = 0; i < pComboBox->GetCount() && nWidth <= ExtConfigs::AdjustDropdownWidth_Max; ++i)
            nWidth = std::max(nWidth, pComboBox->GetLBTextLen(i) * ExtConfigs::AdjustDropdownWidth_Factor);

        nWidth = std::min(nWidth, ExtConfigs::AdjustDropdownWidth_Max);
        pComboBox->SetDroppedWidth(nWidth);
    }

    return 0;
}

DEFINE_HOOK(43CFE4, Miscs_LoadParams_SpeechBubble, 6)
{
    auto AddString = [](HWND hComboBox, const char* lpString)
    {
        SendMessage(hComboBox, CB_ADDSTRING, NULL, (LPARAM)lpString);
    };

    GET(HWND, hComboBox, ECX);
    while (SendMessage(hComboBox, CB_GETCOUNT, 0, NULL) > 0)
        SendMessage(hComboBox, CB_DELETESTRING, 0, 0);
    AddString(hComboBox, "0 - None");
    AddString(hComboBox, "1 - Asterisk(*)");
    AddString(hComboBox, "2 - Question mark(?)");
    AddString(hComboBox, "3 - Exclamation mark(!)");
    return 0x43D037;
}

DEFINE_HOOK(441910, Miscs_LoadParams_TutorialTexts, 7)
{
    GET_STACK(ppmfc::CComboBox*, pComboBox, 0x4);
    if (ExtConfigs::TutorialTexts_Hide)
    {
        pComboBox->DeleteAllStrings();
        return 0x441A34;
    }
    if (ExtConfigs::TutorialTexts_Fix)
    {   
        pComboBox->DeleteAllStrings();
        for (auto x : FA2sp::TutorialTextsMap)
            pComboBox->AddString(x.first + " : " + x.second);
        Logger::Debug("%d csf entities added.\n", FA2sp::TutorialTextsMap.size());
        return 0x441A34;
    }
    return 0;
}

DEFINE_HOOK(441A40, Miscs_LoadParams_Triggers, 6)
{
    GET_STACK(ppmfc::CComboBox*, pComboBox, 0x4);

    pComboBox->DeleteAllStrings();

    auto const pINI = CMapData::GetMapDocument(true);
    pComboBox->LockWindowUpdate();

    if (ExtConfigs::SortByTriggerName && pComboBox->GetDlgCtrlID() == 1402)
    {
        std::map<ppmfc::CString, ppmfc::CString> collector;
        
        if (auto const pSection = pINI->GetSection("Triggers"))
        {
            for (auto pair : pSection->EntitiesDictionary)
            {
                auto splits = STDHelpers::SplitString(pair.second, 2);
                ppmfc::CString buffer(pair.first);
                buffer += " (" + splits[2] + ")";
                collector.insert(std::make_pair(splits[2], buffer));
            }
        }

        for (auto pair : collector)
            pComboBox->AddString(pair.second);

        collector.clear();
    }
    else
    {
        if (auto pSection = pINI->GetSection("Triggers"))
        {
            for (auto& pair : pSection->EntitiesDictionary)
            {
                auto splits = STDHelpers::SplitString(pair.second, 2);
                ppmfc::CString buffer = pair.first;
                buffer += " (" + splits[2] + ")";
                pComboBox->AddString(buffer);
            }
        }
    }

    pComboBox->UnlockWindowUpdate();
    return 0x441DF6;
}
