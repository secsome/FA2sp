#include "Body.h"

#include <Helpers/Macro.h>

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