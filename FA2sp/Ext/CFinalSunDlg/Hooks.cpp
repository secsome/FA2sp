#include "Body.h"

#include <Helpers/Macro.h>

#include <CFinalSunApp.h>

#include "../CIsoView/Body.h"

DEFINE_HOOK(424654, CFinalSunDlg_OnInitDialog_EnableLayersByDefault, 7)
{
    GET(CFinalSunDlg*, pThis, ESI);

    auto pMenu = pThis->GetMenu();

    pMenu->CheckMenuItem(30000, MF_CHECKED);
    pMenu->CheckMenuItem(30001, MF_CHECKED);
    pMenu->CheckMenuItem(30002, MF_CHECKED);
    pMenu->CheckMenuItem(30003, MF_CHECKED);
    pMenu->CheckMenuItem(30004, MF_CHECKED);
    pMenu->CheckMenuItem(30005, MF_CHECKED);
    pMenu->CheckMenuItem(30006, MF_CHECKED);
    pMenu->CheckMenuItem(30007, MF_CHECKED);
    pMenu->CheckMenuItem(30008, MF_CHECKED);
    pMenu->CheckMenuItem(30009, MF_CHECKED);
    pMenu->CheckMenuItem(30010, MF_CHECKED);
    pMenu->CheckMenuItem(30011, MF_CHECKED);
    pMenu->CheckMenuItem(30012, MF_CHECKED);

    return 0;
}

DEFINE_HOOK(432304, CFinalSunDlg_Update_LayersVisibility, 5)
{
    GET(CMenu*, pMenu, ESI);

    auto SetItemCheckStatus = [&pMenu](int id, bool& param)
    {
        pMenu->CheckMenuItem(id, param ? MF_CHECKED : MF_UNCHECKED);
    };

    SetItemCheckStatus(30000, CIsoViewExt::DrawStructures);
    SetItemCheckStatus(30001, CIsoViewExt::DrawInfantries);
    SetItemCheckStatus(30002, CIsoViewExt::DrawUnits);
    SetItemCheckStatus(30003, CIsoViewExt::DrawAircrafts);
    SetItemCheckStatus(30004, CIsoViewExt::DrawBasenodes);
    SetItemCheckStatus(30005, CIsoViewExt::DrawWaypoints);
    SetItemCheckStatus(30006, CIsoViewExt::DrawCelltags);
    SetItemCheckStatus(30007, CIsoViewExt::DrawMoneyOnMap);
    SetItemCheckStatus(30008, CIsoViewExt::DrawOverlays);
    SetItemCheckStatus(30009, CIsoViewExt::DrawTerrains);
    SetItemCheckStatus(30010, CIsoViewExt::DrawSmudges);
    SetItemCheckStatus(30011, CIsoViewExt::DrawTubes);
    SetItemCheckStatus(30012, CIsoViewExt::DrawBounds);

    return 0;
}

#include "../../Helpers/Translations.h"

DEFINE_HOOK(43209D, CFinalSunDlg_Update_TranslateMenuItems, A)
{
    // GET_STACK(CFinalSunDlg*, pThis, STACK_OFFS(0x60, 0x3C));
    // auto pMenu = pThis->GetMenu();
    
    GET(CMenu*, pMenu, ESI);

    auto translateMenuItem = [&pMenu](int id, ppmfc::CString pSrcName)
    {
        ppmfc::CString buffer;
        if (Translations::GetTranslationItem(pSrcName, buffer))
        {
            buffer.Replace("\\t", "\t");
            pMenu->ModifyMenu(id, MF_BYCOMMAND, id, buffer);
        }
    };

    auto translateSubMenu = [&pMenu](int pos, ppmfc::CString pSrcName)
    {
        ppmfc::CString buffer;
        if (Translations::GetTranslationItem(pSrcName, buffer))
        {
            pMenu->ModifyMenu(pos, MF_BYPOSITION, pos, buffer);
        }
    };

    int i = 0;
    translateSubMenu(i++, "Menu.File");
    translateMenuItem(57600, "Menu.File.New");
    translateMenuItem(40001, "Menu.File.Open");
    translateMenuItem(57603, "Menu.File.Save");
    translateMenuItem(40002, "Menu.File.SaveAs");
    translateMenuItem(40025, "Menu.File.CheckMap");
    // translateMenuItem(40017, "Menu.File.RunGame");
    translateMenuItem(40003, "Menu.File.Quit");

    translateSubMenu(i++, "Menu.Edit");
    translateMenuItem(57643, "Menu.Edit.Undo");
    translateMenuItem(57644, "Menu.Edit.Redo");
    translateMenuItem(57634, "Menu.Edit.Copy");
    translateMenuItem(40109, "Menu.Edit.CopyWholeMap");
    translateMenuItem(57637, "Menu.Edit.Paste");
    translateMenuItem(40110, "Menu.Edit.PasteCentered");
    translateMenuItem(40040, "Menu.Edit.Map");
    translateMenuItem(40036, "Menu.Edit.Basic");
    translateMenuItem(40038, "Menu.Edit.SpecialFlags");
    translateMenuItem(40043, "Menu.Edit.Lighting");
    translateMenuItem(40039, "Menu.Edit.Houses");
    translateMenuItem(40076, "Menu.Edit.TriggerEditor");
    translateMenuItem(40042, "Menu.Edit.TagEditor");
    translateMenuItem(40046, "Menu.Edit.Taskforces");
    translateMenuItem(40044, "Menu.Edit.Scripts");
    translateMenuItem(40045, "Menu.Edit.Teams");
    translateMenuItem(40047, "Menu.Edit.AITriggers");
    translateMenuItem(40048, "Menu.Edit.AITriggerEnable");
    translateMenuItem(40082, "Menu.Edit.LocalVariables");
    translateMenuItem(40037, "Menu.Edit.SingleplayerSettings");
    translateMenuItem(40049, "Menu.Edit.INIEditor");

    translateSubMenu(i++, "Menu.Terrain");
    translateMenuItem(40053, "Menu.Terrain.RaiseGround");
    translateMenuItem(40054, "Menu.Terrain.LowerGround");
    translateMenuItem(40064, "Menu.Terrain.FlattenGround");
    translateMenuItem(40065, "Menu.Terrain.HideTileset");
    translateMenuItem(40066, "Menu.Terrain.ShowEveryTileset");
    translateMenuItem(40072, "Menu.Terrain.HideSingleField");
    translateMenuItem(40071, "Menu.Terrain.ShowAllFields");
    translateMenuItem(40062, "Menu.Terrain.RaiseSingleTile");
    translateMenuItem(40063, "Menu.Terrain.LowerSingleTile");

    translateSubMenu(i++, "Menu.MapTools");
    translateMenuItem(40077, "Menu.MapTools.ChangeMapHeight");
    translateMenuItem(40096, "Menu.MapTools.AutoCreateShores");
    translateMenuItem(40085, "Menu.MapTools.AutoLevelUsingCliffs");
    translateMenuItem(40092, "Menu.MapTools.PaintCliffFront");
    translateMenuItem(40093, "Menu.MapTools.PaintCliffBack");
    translateMenuItem(40133, "Menu.MapTools.SearchWaypoint");
    translateMenuItem(40135, "Menu.MapTools.ToolScripts");

    if (0)
    {
        translateSubMenu(i++, "Menu.Online");
        translateMenuItem(40078, "Menu.Online.Westwood");
        translateMenuItem(40081, "Menu.Online.FA2Fansite");
        translateMenuItem(40119, "Menu.Online.FA2Forum");
    }

    translateSubMenu(i++, "Menu.Options");
    translateMenuItem(40004, "Menu.Options.Settings");
    translateMenuItem(40024, "Menu.Options.ShowMinimap");
    translateMenuItem(40023, "Menu.Options.Easymode");
    translateMenuItem(40118, "Menu.Options.Sounds");
    translateMenuItem(40123, "Menu.Options.ShowBuildingOutline");
    translateMenuItem(40104, "Menu.Options.DisableAutoShore");
    translateMenuItem(40105, "Menu.Options.DisableAutoLAT");
    translateMenuItem(40120, "Menu.Options.DisableSlopeCorrection");

    translateSubMenu(i++, "Menu.Help");
    translateMenuItem(57670, "Menu.Help.Manual");
    translateMenuItem(40006, "Menu.Help.Info");
    translateMenuItem(40075, "Menu.Help.Credits");
    translateMenuItem(40022, "Menu.Help.TipOfTheDay");

    translateSubMenu(i++, "Menu.Layers");
    translateMenuItem(30000, "Menu.Layers.Structures");
    translateMenuItem(30001, "Menu.Layers.Infantries");
    translateMenuItem(30002, "Menu.Layers.Units");
    translateMenuItem(30003, "Menu.Layers.Aircrafts");
    translateMenuItem(30004, "Menu.Layers.Basenodes");
    translateMenuItem(30005, "Menu.Layers.Waypoints");
    translateMenuItem(30006, "Menu.Layers.Celltags");
    translateMenuItem(30007, "Menu.Layers.MoneyOnMap");
    translateMenuItem(30008, "Menu.Layers.Overlays");
    translateMenuItem(30009, "Menu.Layers.Terrains");
    translateMenuItem(30010, "Menu.Layers.Smudges");
    translateMenuItem(30011, "Menu.Layers.Tubes");
    translateMenuItem(30012, "Menu.Layers.Bounds");

    return 0x432304;
}

DEFINE_HOOK(432010, CFinalSunDlg_Update_NoFuckingEasyMode, 7)
{
    CFinalSunApp::Instance->EasyMode = false;
    return 0;
}