#pragma once

#include <FA2PP.h>

#include <CIsoView.h>
#include "../FA2Expand.h"

struct CellData;

class NOVTABLE CIsoViewExt : public CIsoView
{
public:
    static double constexpr ONE_THIRD = 1 / 3.0;
    static double constexpr ONE_SIXTH = 1 / 6.0;

    static void ProgramStartupInit();

    BOOL PreTranslateMessageExt(MSG* pMsg);

    BOOL OnMouseWheelExt(UINT Flags, short zDelta, CPoint pt);

    void OnDraw();
    void CalculateViewBounds(LONG& rect_X, LONG& rect_Y, int& Coord_X, int& Coord_Y);

    void DrawLockedCellOutline(int X, int Y, int W, int H, COLORREF color, bool bUseDot, bool bUsePrimary, LPDDSURFACEDESC2 lpDesc);
    void DrawCelltag(int X, int Y);
    void DrawWaypoint(int WPIndex, int X, int Y);
    void DrawTube(CellData* pData, int X, int Y);

    static bool DrawStructures;
    static bool DrawInfantries;
    static bool DrawUnits;
    static bool DrawAircrafts;
    static bool DrawBasenodes;
    static bool DrawWaypoints;
    static bool DrawCelltags;
    static bool DrawMoneyOnMap;
    static bool DrawOverlays;
    static bool DrawTerrains;
    static bool DrawSmudges;
    static bool DrawTubes;
    static bool DrawBounds;
};