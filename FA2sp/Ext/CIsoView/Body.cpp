#include "Body.h"

#include "../../FA2sp.h"

#include <WindowsX.h>

bool CIsoViewExt::DrawStructures = true;
bool CIsoViewExt::DrawInfantries = true;
bool CIsoViewExt::DrawUnits = true;
bool CIsoViewExt::DrawAircrafts = true;
bool CIsoViewExt::DrawBasenodes = true;
bool CIsoViewExt::DrawWaypoints = true;
bool CIsoViewExt::DrawCelltags = true;
bool CIsoViewExt::DrawMoneyOnMap = true;
bool CIsoViewExt::DrawOverlays = true;
bool CIsoViewExt::DrawTerrains = true;
bool CIsoViewExt::DrawSmudges = true;
bool CIsoViewExt::DrawTubes = true;
bool CIsoViewExt::DrawBounds = true;

void CIsoViewExt::ProgramStartupInit()
{
    // RunTime::ResetMemoryContentAt(0x594518, CIsoViewExt::PreTranslateMessageExt);
}

BOOL CIsoViewExt::PreTranslateMessageExt(MSG* pMsg)
{
    switch (pMsg->message)
    {
    case WM_MOUSEWHEEL:
        return this->OnMouseWheel(
            GET_KEYSTATE_WPARAM(pMsg->wParam),
            GET_WHEEL_DELTA_WPARAM(pMsg->wParam),
            { GET_X_LPARAM(pMsg->lParam) ,GET_Y_LPARAM(pMsg->lParam) });
    }
    return CIsoView::PreTranslateMessage(pMsg);
}

BOOL CIsoViewExt::OnMouseWheelExt(UINT Flags, short zDelta, CPoint point)
{
    int nRealStep = zDelta / WHEEL_DELTA;
    if (nRealStep == 0) return FALSE;
    
    if (nRealStep > 0) //GoUp
    {

    }
    
    return TRUE;
}
