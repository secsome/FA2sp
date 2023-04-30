#include "CIsoView.h"

#include <CTileTypeClass.h>

void CIsoViewImpl::ScreenCoord2MapCoord_Flat(int& X, int& Y)
{
    double x = X * 1.0 / 60;
    double y = Y * 1.0 / 30;
    X = y - x + CMapData::Instance->MapWidthPlusHeight * 0.5 + 1.5;
    Y = y + x - CMapData::Instance->MapWidthPlusHeight * 0.5 + 0.5;
}

void CIsoViewImpl::ScreenCoord2MapCoord_Height(int& X, int& Y)
{
    auto const nWH = CMapData::Instance->MapWidthPlusHeight;
    int originX = X;
    int originY = Y;
    CIsoViewImpl::ScreenCoord2MapCoord_Flat(X, Y);
    X -= Y;
    Y += 15;
    
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            MapCoord mapCoord{ X + Y,Y };
            if (j == 1)
                --mapCoord.X;
            else if (j == 2)
                --mapCoord.Y;

            if (mapCoord.X >= 0 && mapCoord.Y >= 0 && mapCoord.X < nWH && mapCoord.Y < nWH)
            {
                auto pCell = CMapData::Instance->TryGetCellAt(mapCoord.X, mapCoord.Y);
                int nTileIdx = pCell->TileIndex == 0xFFFF ? 0 : pCell->TileIndex;
                if (!pCell->Flag.IsHiddenCell && !(*CTileTypeClass::Instance)[nTileIdx].IsHidden)
                {
                    const int y = originY - 15 * (mapCoord.X + mapCoord.Y - pCell->Height);
                    auto const yy = (y - 15) * 0.033333335;
                    auto const xx = (originX - 30 * (nWH + mapCoord.Y - mapCoord.X)) * 0.016666668;
                    if (!static_cast<int>(yy - xx + 1.0) && !static_cast<int>(xx + yy) || // -2 < yy - xx < 0 && -1 < x+y < 1
                        !CIsoViewImpl::ControlKeyIsDown && y > 30)
                    {
                        X = mapCoord.X;
                        Y = mapCoord.Y;
                        return;
                    }
                }
            }
            --Y;
        }
    }

    X = -1;
    Y = -1;
}

void CIsoViewImpl::MapCoord2ScreenCoord_Flat(int& X, int& Y)
{
    int originY = Y;
    Y = 15 * (X + Y);
    X = 30 * (originY + CMapData::Instance->MapWidthPlusHeight - X);
}

void CIsoViewImpl::MapCoord2ScreenCoord_Height(int& X, int& Y)
{
    CIsoViewImpl::MapCoord2ScreenCoord_Flat(X, Y);
    Y -= 15 * CMapData::Instance->GetCellAt(X, Y)->Height;
}

void CIsoViewImpl::ScreenCoord2MapCoord(int& X, int& Y)
{
    if (CFinalSunApp::Instance->FlatToGround)
        ScreenCoord2MapCoord_Flat(X, Y);
    else
        ScreenCoord2MapCoord_Height(X, Y);
}

void CIsoViewImpl::MapCoord2ScreenCoord(int& X, int& Y)
{
    if (CFinalSunApp::Instance->FlatToGround)
        MapCoord2ScreenCoord_Flat(X, Y);
    else
        MapCoord2ScreenCoord_Height(X, Y);
}

MapCoord CIsoViewImpl::GetCurrentMapCoord(const CPoint& point)
{
    RECT rect;
    this->GetWindowRect(&rect);
    return CIsoViewImpl::GetCurrentMapCoord(point, rect);
}

MapCoord CIsoViewImpl::GetCurrentMapCoord(const CPoint& point, const CPoint& lt)
{
    int x = point.x + lt.x + ViewPosition.x;
    int y = point.y + lt.y + ViewPosition.y;
    ScreenCoord2MapCoord(x, y);
    return MapCoord{ x,y };
}

MapCoord CIsoViewImpl::GetCurrentMapCoord(const CPoint& point, const CRect& rect)
{
    int x = point.x + rect.left + ViewPosition.x;
    int y = point.y + rect.top + ViewPosition.y;
    ScreenCoord2MapCoord(x, y);
    return MapCoord{ x,y };
}
