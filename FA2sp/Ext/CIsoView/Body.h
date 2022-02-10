#pragma once

#include <FA2PP.h>

#include <CIsoView.h>
#include "../FA2Expand.h"

struct CellData;

class NOVTABLE CIsoViewExt : public CIsoView
{
public:
    static void ProgramStartupInit();

    BOOL PreTranslateMessageExt(MSG* pMsg);

    BOOL OnMouseWheelExt(UINT Flags, short zDelta, CPoint pt);

    void DrawLockedCellOutline(int X, int Y, int W, int H, COLORREF color, bool bUseDot, bool bUsePrimary, LPDDSURFACEDESC2 lpDesc);
    void DrawCelltag(int X, int Y);
    void DrawWaypointFlag(int X, int Y);
    void DrawTube(CellData* pData, int X, int Y);

    void AddTube(int EnterX, int EnterY, int ExitX, int ExitY);

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