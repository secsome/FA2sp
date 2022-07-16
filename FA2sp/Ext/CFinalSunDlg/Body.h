#pragma once

#include "../FA2Expand.h"
#include <CFinalSunDlg.h>

#include <array>
#include <set>
#include <map>
#include <memory>

#include <CPropertyBuilding.h>
#include <CPropertyAircraft.h>
#include <CPropertyInfantry.h>
#include <CPropertyUnit.h>

class NOVTABLE CFinalSunDlgExt : CFinalSunDlg
{
public:
    static void ProgramStartupInit();

    static int CurrentLighting;

    BOOL PreTranslateMessageExt(MSG* pMsg);
    BOOL OnCommandExt(WPARAM wParam, LPARAM lParam);
};

class CViewObjectsExt : public CViewObjects
{
    enum {
        Root_Nothing = 0, Root_Ground, Root_Owner, Root_Infantry, Root_Vehicle,
        Root_Aircraft, Root_Building, Root_Terrain, Root_Smudge, Root_Overlay,
        Root_Waypoint, Root_Celltag, Root_Basenode, Root_Tunnel, Root_PlayerLocation,
        Root_PropertyBrush, Root_Delete, Root_Count
    };

    enum {
        Set_Building = 0, Set_Infantry, Set_Vehicle, Set_Aircraft, Set_Count
    };

    enum
    {
        Const_Infantry = 10000, Const_Building = 20000, Const_Aircraft = 30000,
        Const_Vehicle = 40000, Const_Terrain = 50000, Const_Overlay = 63000,
        Const_House = 70000, Const_Smudge = 80000, Const_PropertyBrush = 90000
    };

    static std::array<HTREEITEM, Root_Count> ExtNodes;
    static std::set<ppmfc::CString> IgnoreSet;
    static std::set<ppmfc::CString> ForceName;
    static std::set<ppmfc::CString> ExtSets[Set_Count];
    static std::map<ppmfc::CString, int> KnownItem;
    static std::map<ppmfc::CString, int> Owners;
    static std::unique_ptr<CPropertyBuilding> BuildingBrushDlg;
    static std::unique_ptr<CPropertyInfantry> InfantryBrushDlg;
    static std::unique_ptr<CPropertyUnit> VehicleBrushDlg;
    static std::unique_ptr<CPropertyAircraft> AircraftBrushDlg;

    HTREEITEM InsertString(const char* pString, DWORD dwItemData = 0, 
        HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
    HTREEITEM InsertTranslatedString(const char* pOriginString, DWORD dwItemData = 0,
        HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
    void Redraw_Initialize();
    void Redraw_MainList();
    void Redraw_Ground();
    void Redraw_Owner();
    void Redraw_Infantry();
    void Redraw_Vehicle();
    void Redraw_Aircraft();
    void Redraw_Building();
    void Redraw_Terrain();
    void Redraw_Smudge();
    void Redraw_Overlay();
    void Redraw_Waypoint();
    void Redraw_Celltag();
    void Redraw_Basenode();
    void Redraw_Tunnel();
    void Redraw_PlayerLocation();
    void Redraw_PropertyBrush();

    bool DoPropertyBrush_Building();
    bool DoPropertyBrush_Infantry();
    bool DoPropertyBrush_Vehicle();
    bool DoPropertyBrush_Aircraft();

public:
    static bool BuildingBrushBools[14];
    static bool InfantryBrushBools[10];
    static bool VehicleBrushBools[11];
    static bool AircraftBrushBools[9];
    static bool InitPropertyDlgFromProperty;

    void Redraw();
    bool UpdateEngine(int nData);
    static void OnExeTerminate();
    static void ApplyPropertyBrush(int X, int Y);
    static void ApplyPropertyBrush_Building(int nIndex);
    static void ApplyPropertyBrush_Infantry(int nIndex);
    static void ApplyPropertyBrush_Aircraft(int nIndex);
    static void ApplyPropertyBrush_Vehicle(int nIndex);
    
    static bool IsIgnored(const char* pItem);

    ppmfc::CString QueryUIName(const char* pRegName, bool bOnlyOneLine = true);

public:
    /// <summary>
    /// Guess which type does the item belongs to.
    /// </summary>
    /// <param name="pRegName">Reg name of the given item.</param>
    /// <returns>
    /// The index of type guessed. -1 if cannot be guessed.
    /// 0 = Building, 1 = Infantry, 2 = Vehicle, 3 = Aircraft
    /// </returns>
    static int GuessType(const char* pRegName);
    /// <summary>
    /// Guess which side does the item belongs to.
    /// </summary>
    /// <param name="pRegName">Reg name of the given item.</param>
    /// <param name="nType">
    /// Which type does this item belongs to.
    /// 0 = Building, 1 = Infantry, 2 = Vehicle, 3 = Aircraft
    /// </param>
    /// <returns>The index of side guessed. -1 if cannot be guessed.</returns>
    static int GuessSide(const char* pRegName, int nType);
    /// <summary>
    /// Guess which side does the item belongs to.
    /// </summary>
    /// <param name="pRegName">Reg name of the given item.</param>
    /// <returns>The index of side guessed. -1 if cannot be guessed.</returns>
    static int GuessBuildingSide(const char* pRegName);
    /// <summary>
    /// Guess which side does the item belongs to.
    /// </summary>
    /// <param name="pRegName">Reg name of the given item.</param>
    /// <param name="nType">
    /// Which type does this item belongs to.
    /// 0 = Building, 1 = Infantry, 2 = Vehicle, 3 = Aircraft
    /// </param>
    /// <returns>The index of side guessed. -1 if cannot be guessed.</returns>
    static int GuessGenericSide(const char* pRegName, int nType);
};
