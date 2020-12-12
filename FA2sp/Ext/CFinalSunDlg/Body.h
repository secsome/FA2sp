#pragma once

#include <CFinalSunDlg.h>

#include <unordered_map>

class CFinalSunDlgExt
{

};



class ObjectBrowserControlExt : public ObjectBrowserControl
{
    enum {
        Root_Nothing = 0, Root_Ground, Root_Owner, Root_Infantry, Root_Vehicle,
        Root_Aircraft, Root_Building, Root_Terrain, Root_Smudge, Root_Overlay,
        Root_Waypoint, Root_Celltag, Root_Basenode, Root_PlayerLocation, Root_Delete
    };

    static std::unordered_map<int, HTREEITEM> ExtNodes;
    HTREEITEM InsertString(const char* pString, DWORD dwItemData = 0, 
        HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
    HTREEITEM InsertTranslatedString(const char* pOriginString, DWORD dwItemData = 0,
        HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
    void Redraw_Clear();
    void Redraw_MainList();
    void Redraw_Owner();
public:
    void Redraw();

public:
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
};
