#include "Body.h"

#include "../../Helpers/Translations.h"
#include "../../Helpers/STDHelpers.h"

#include <GlobalVars.h>

std::unordered_map<int, HTREEITEM> ObjectBrowserControlExt::ExtNodes;

HTREEITEM ObjectBrowserControlExt::InsertString(const char* pString, DWORD dwItemData,
    HTREEITEM hParent, HTREEITEM hInsertAfter)
{
    return this->InsertItem(5, pString, 0, 0, 0, 0, dwItemData, hParent, hInsertAfter);
}

HTREEITEM ObjectBrowserControlExt::InsertTranslatedString(const char* pOriginString, DWORD dwItemData,
    HTREEITEM hParent, HTREEITEM hInsertAfter)
{
    CString buffer;
    Translations::GetTranslationItem(pOriginString, buffer);
    return InsertString(buffer, dwItemData, hParent, hInsertAfter);
}

/*
* A HUGE PROJECT FOR REPLACING FA2
* ObjectBrowserControl TO EXTEND ITS FEATURES
* FA2 USES ITEMDATA TO KNOW WHAT SHOULD BE DRAWN
* CONSTANT + INDEX
* CONSTANT LIST:
* INFANTRY = 10000
* BUILDING = 20000
* AIRCRAFT = 30000
* VEHICLE  = 40000
* TERRAIN  = 50000
* OVERLAY  = 63000
* HOUSES   = 70000
* SMUDGE   = 80000
*/
void ObjectBrowserControlExt::Redraw()
{
    Redraw_Clear();
    Redraw_MainList();
    Redraw_Owner();
}

void ObjectBrowserControlExt::Redraw_Clear()
{
    ExtNodes.clear();
    this->DeleteAllItems();
}

void ObjectBrowserControlExt::Redraw_MainList()
{
    ExtNodes[Root_Nothing] = this->InsertTranslatedString("NothingObList", -2);
    ExtNodes[Root_Owner] = this->InsertTranslatedString("ChangeOwnerObList");
    ExtNodes[Root_Infantry] = this->InsertTranslatedString("InfantryObList", 0);
    ExtNodes[Root_Vehicle] = this->InsertTranslatedString("VehiclesObList", 1);
    ExtNodes[Root_Aircraft] = this->InsertTranslatedString("AircraftObList", 2);
    ExtNodes[Root_Building] = this->InsertTranslatedString("StructuresObList", 3);
    ExtNodes[Root_Terrain] = this->InsertTranslatedString("TerrainObList", 4);
    ExtNodes[Root_Smudge] = this->InsertTranslatedString("SmudgesObList", 10);
    ExtNodes[Root_Overlay] = this->InsertTranslatedString("OverlayObList", 5);
    ExtNodes[Root_Waypoint] = this->InsertTranslatedString("WaypointsObList", 6);
    ExtNodes[Root_Celltag] = this->InsertTranslatedString("CelltagsObList", 7);
    ExtNodes[Root_Basenode] = this->InsertTranslatedString("BaseNodesObList", 8);
    ExtNodes[Root_PlayerLocation] = this->InsertTranslatedString("StartpointsObList", 12);
    ExtNodes[Root_Delete] = this->InsertTranslatedString("DelObjObList", 10);
}

void ObjectBrowserControlExt::Redraw_Owner()
{
    HTREEITEM& hOwner = ExtNodes[Root_Owner];
    if (hOwner == NULL)    return;

    auto& rules = GlobalVars::INIFiles::Rules();
}

int ObjectBrowserControlExt::GuessSide(const char* pRegName, int nType)
{
    auto& rules = GlobalVars::INIFiles::Rules();
    int nSideCount = rules.GetKeyCount("Sides");

    switch (nType)
    {
    case 0:
    {
        int planning = atoi(rules.GetString(pRegName, "AIBasePlanningSide", "-1"));
        if (planning >= nSideCount)  return -1;
        if (planning >= 0)
            return planning;
        else
        {
            auto& conyards = STDHelpers::SplitString(rules.GetString("AI", "BuildConst"));
            auto itr = std::lower_bound(conyards.begin(), conyards.end(), pRegName);
            if (itr != conyards.end())
                return itr - conyards.begin();
        }
        break;
    }
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        return -1;
    }

    auto GuessByEnum = []()
    {

    };

    for (auto& prerequest : STDHelpers::SplitString(rules.GetString(pRegName, "Prerequisite", "")))
    {
        if (rules.KeyExists("GenericPrerequisites", prerequest))
        {
            for (auto& subprere : STDHelpers::SplitString(rules.GetString("GenericPrerequisites", prerequest, "")))
            {
                
                if (int guess = GuessSide(subprere, 0) != -1)
                    return guess;
            }
        }
    }
    return -1;
}