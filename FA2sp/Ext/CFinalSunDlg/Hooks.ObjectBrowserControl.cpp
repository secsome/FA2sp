#include "Body.h"

#include <FA2PP.h>
#include <Helpers/Macro.h>
#include <GlobalVars.h>

#include "../../FA2sp.h"

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
* 
* LPARAMS LIST:
* 
* TVI_ROOT
* |     NOTHING = -2
* |     UNKNOWN = 0
* 
* |     TILES
* |     |     CLEAR = 61
* |     |     SAND  = 62
* |     |     ROUGH = 63
* |     |     WATER = 64
* |     |     GREEN = 65
* |     |     PAVE  = 66
* |     |     PAVE2 = 67 (New Urban Only)
* |
* |
* |     WAYPOINTS
* |     |     CREATE = 20
* |     |     DELETE = 21 (Also Del StartingPoint)
* |     |     CREATE_SPECIFIC = 22
* |     
* |     CELLTAGS
* |     |     CREATE = 36
* |     |     DELETE = 37
* |     |     EDIT_PROPERTY = 38
* |     |     
* |          
* |     BASENODES     
* |     |     CREATE_NO_DELETE = 40
* |     |     CREATE_DELETE = 41
* |     |     DELETE_NODE = 42
* |     |     
* |     
* |     OVERLAYS     
* |     |     ERASE
* |     |     |     SINGLE = 60100
* |     |     |     ONE_BLOCK = 60101
* |     |     |     TWO_BLOCK = 60102
* |     |     |     THREE_BLOCK = 60103
* |     |
* |     |     ORE&GEMS
* |     |     |     TIBERIUM = 60210
* |     |     |     GEM = 60310
* |     |     
* |     |     BRIDGES
* |     |     |     SMALL = 60501
* |     |     |     BIG = 60500 
* |     |     |     BIG_TRACK = 60502
* |     |     |     SMALL_CONCRETE = 60503
* |     |     
* |     |     OTHERS
* |     |     
* |     |     ALL
* |     |     
* |     |     SET_OVERLAY_MANUALLY = 60001
* |     |     
* |     |     SET_OVERLAY_DATA_MANUALLY = 60002
* |     |     
* |     
* |     TUNNEL
* |     |     NEW = 50
* |     |     DEL = 51
* |          
* |     TERRAINS     
* |     |     TREES
* |     |     |     RANDOM_TREE = 50999
* |     |     |     
* |     |     |     
* |     |     |     
* |     |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* |     |     
* 
*/

DEFINE_HOOK(51D3DE, ObjectBrowserControl_Redraw, 5)
{
    GET(CTreeCtrl*, pTree, ESI);
    GET(HTREEITEM, pParent, EDI);
    
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "InfantryTest", 0, 0, 0, 0, 10000, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "BuildingTest", 0, 0, 0, 0, 20000, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "AircraftTest", 0, 0, 0, 0, 30000, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "VehicleTest", 0, 0, 0, 0, 40000, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "TerrainTest", 0, 0, 0, 0, 50001, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "OverlayTest", 0, 0, 0, 0, 63260, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "HouseTest", 0, 0, 0, 0, 70005, TVI_ROOT, TVI_LAST);
    pTree->InsertItem(TVIF_TEXT | TVIF_PARAM, "SmudgeTest", 0, 0, 0, 0, 80001, TVI_ROOT, TVI_LAST);

    return 0;
}

//void PrintNode(CTreeCtrl* pTree, HTREEITEM hNode)
//{
//    if (pTree->ItemHasChildren(hNode))
//    {
//        HTREEITEM hNextItem;
//        HTREEITEM hChildItem = pTree->GetChildItem(hNode);
//
//        while (hChildItem != NULL)
//        {
//            if (pTree->ItemHasChildren(hChildItem))
//                PrintNode(pTree, hChildItem);
//            hNextItem = pTree->GetNextItem(hChildItem, TVGN_NEXT);
//
//            Logger::Debug("%s %d\n", pTree->GetItemText(hChildItem), pTree->GetItemData(hChildItem));
//
//            hChildItem = hNextItem;
//        }
//    }
//}
//
//DEFINE_HOOK(523139, ObjectBrowserControl_Redraw_End, 5)
//{
//    GET(CTreeCtrl*, pTree, ESI);
//    auto hRoot = pTree->GetSelectedItem();
//    
//    PrintNode(pTree, hRoot);
//    
//    return 0;
//}