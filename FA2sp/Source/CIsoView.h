#pragma once

#include <CIsoView.h>

class CIsoViewImpl : public CIsoView
{
public:
    static void ScreenCoord2MapCoord(int& X, int& Y);
    static void MapCoord2ScreenCoord(int& X, int& Y);

    MapCoord GetCurrentMapCoord(const CPoint& point);
    MapCoord GetCurrentMapCoord(const CPoint& point, const CPoint& lt);
    MapCoord GetCurrentMapCoord(const CPoint& point, const CRect& rect);
protected:
    static void ScreenCoord2MapCoord_Flat(int& X, int& Y);
    static void ScreenCoord2MapCoord_Height(int& X, int& Y);

    static void MapCoord2ScreenCoord_Flat(int& X, int& Y);
    static void MapCoord2ScreenCoord_Height(int& X, int& Y);
};