#include "Body.h"

#include "../../FA2sp.h"

#include <WindowsX.h>
#include <CPalette.h>

#include <CMapData.h>
#include <Drawing.h>
#include <CINI.h>

#include <ranges>

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

void CIsoViewExt::AddTube(int EnterX, int EnterY, int ExitX, int ExitY)
{
    Logger::FormatLog("Generating tube from ({}, {}) to ({}, {})\n", EnterX, EnterY, ExitX, ExitY);

    TubeData tube;
    memset(tube.Directions, 0xFF, sizeof(tube.Directions));
    tube.EnterX = EnterX;
    tube.EnterY = EnterY;
    tube.ExitX = ExitX;
    tube.ExitY = ExitY;
    
    int nTubeSteps = 0;
    MapCoord coordToMove = { tube.EnterX - tube.ExitX,tube.EnterY - tube.ExitY };
    while (true)
    {
        if (coordToMove.Y < 0 && coordToMove.X < 0)
        {
            coordToMove += MapCoord::Facings[FACING_SOUTH];
            tube.Directions[nTubeSteps++] = FACING_SOUTH;
        }
        else if (coordToMove.Y < 0 && coordToMove.X > 0)
        {
            coordToMove += MapCoord::Facings[FACING_EAST];
            tube.Directions[nTubeSteps++] = FACING_EAST;
        }
        else if (coordToMove.Y < 0 && coordToMove.X == 0)
        {
            coordToMove += MapCoord::Facings[FACING_SOUTHEAST];
            tube.Directions[nTubeSteps++] = FACING_SOUTHEAST;
        }
        else if (coordToMove.Y > 0 && coordToMove.X < 0)
        {
            coordToMove += MapCoord::Facings[FACING_WEST];
            tube.Directions[nTubeSteps++] = FACING_WEST;
        }
        else if (coordToMove.Y > 0 && coordToMove.X > 0)
        {
            coordToMove += MapCoord::Facings[FACING_NORTH];
            tube.Directions[nTubeSteps++] = FACING_NORTH;
        }
        else if (coordToMove.Y > 0 && coordToMove.X == 0)
        {
            coordToMove += MapCoord::Facings[FACING_NORTHWEST];
            tube.Directions[nTubeSteps++] = FACING_NORTHWEST;
        }
        else if (coordToMove.Y == 0 && coordToMove.X < 0)
        {
            coordToMove += MapCoord::Facings[FACING_SOUTHWEST];
            tube.Directions[nTubeSteps++] = FACING_WEST;
        }
        else if (coordToMove.Y == 0 && coordToMove.X > 0)
        {
            coordToMove += MapCoord::Facings[FACING_NORTHEAST];
            tube.Directions[nTubeSteps++] = FACING_NORTHEAST;
        }
        else
        {
            // coordToMove.Y == 0 && coordToMove.X == 0
            break;
        }

        if (nTubeSteps > 100)
        {
            ::MessageBox(NULL, "Cannot generate a too long tube!", "Error", MB_OK);
            return;
        }
    }
    if (nTubeSteps == 0)
        return;
    tube.EnterFacing = tube.Directions[0];
    CMapData::Instance->AddTube(&tube);
    
    // Add a reversed tube
    std::swap(tube.EnterX, tube.ExitX);
    std::swap(tube.EnterY, tube.ExitY);
    
    auto GetOppositeFacing = [](int nFacing) -> char
    {
        switch (nFacing)
        {
        case FACING_NORTHEAST:
            return FACING_SOUTHWEST;

        case FACING_EAST:
            return FACING_WEST;

        case FACING_SOUTHEAST:
            return FACING_NORTHWEST;

        case FACING_SOUTH:
            return FACING_NORTH;

        case FACING_SOUTHWEST:
            return FACING_NORTHEAST;

        case FACING_WEST:
            return FACING_EAST;

        case FACING_NORTHWEST:
            return FACING_SOUTHEAST;

        case FACING_NORTH:
            return FACING_SOUTH;

        default:
        case FACING_INVALID:
            return FACING_INVALID;
        }
    };

    tube.EnterFacing = GetOppositeFacing(tube.EnterFacing);

    for (char* p = tube.Directions, *q = tube.Directions + nTubeSteps - 1; p <= q; ++p, --q)
    {
        char tmp = *p;
        *p = GetOppositeFacing(*q);
        *q = GetOppositeFacing(tmp);
    }

    CMapData::Instance->AddTube(&tube);
}

void CIsoViewExt::DrawLockedCellOutline(int X, int Y, int W, int H, COLORREF color, bool bUseDot, bool bUsePrimary, LPDDSURFACEDESC2 lpDesc)
{   
    if (lpDesc->lpSurface == nullptr)
        return;

    RECT rect;
    this->GetWindowRect(&rect);

    auto lPitch = lpDesc->lPitch;
    auto nBytesPerPixel = *(int*)0x72A8C0;

    auto pRGB = (ColorStruct*)&color;
    BGRStruct ddColor;
    ddColor.R = pRGB->red;
    ddColor.G = pRGB->green;
    ddColor.B = pRGB->blue;

    auto DrawLine = [lPitch, nBytesPerPixel, ddColor, lpDesc, &rect](int X1, int Y1, int X2, int Y2)
    {
        int color = *(int*)&ddColor;

        if (X1 > X2) 
        {
            std::swap(X1, X2);
            std::swap(Y1, Y2);
        }

        int dx = X2 - X1;
        int dy = Y2 - Y1;

        auto ptr = (unsigned char*)lpDesc->lpSurface + lPitch * Y1 + X1 * nBytesPerPixel;

        if (dy == 0) 
        {
            for (int i = 0; i <= dx; ++i) 
            {
                memcpy(ptr, &ddColor, nBytesPerPixel);
                ptr += nBytesPerPixel;
            }
        }
        else if (dx == 0) 
        {
            int pitch = lPitch;
            if (dy < 0)
            {
                pitch = -pitch;
                dy = -dy;
            }

            for (int i = 0; i <= dy; ++i) 
            {
                memcpy(ptr, &ddColor, nBytesPerPixel);
                ptr += pitch;
            }
        }
        else 
        {
            int pitch = lPitch;
            if (dy < 0)
            {
                pitch = -pitch;
                dy = -dy;
            }

            int dx2 = 2 * dx;
            int dy2 = 2 * dy;

            if (dx > dy) 
            {
                int delta = dy2 - dx;
                for (int i = 0; i < dx; ++i) 
                {
                    memcpy(ptr + i * nBytesPerPixel, &ddColor, nBytesPerPixel);
                    if (delta > 0)
                    {
                        ptr += pitch;
                        delta -= dx2;
                    }
                    delta += dy2;
                }
            }
            else 
            {
                int delta = dx2 - dy;
                int k = 0;

                for (int i = 0; i < dy; ++i)
                {
                    memcpy(ptr + k * nBytesPerPixel, &ddColor, nBytesPerPixel);
                    if (delta > 0) 
                    {
                        ++k;
                        delta -= dy2;
                    }
                    delta += dx2;
                    ptr += pitch;
                }
            }
        }
    };
    auto ClipAndDrawLine = [&rect, DrawLine](int X1, int Y1, int X2, int Y2)
    {
        auto encode = [&rect](int x, int y)
        {
            int c = 0;
            if (x < rect.left) c = c | 0x1;
            else if (x > rect.right) c = c | 0x2;
            if (y > rect.bottom) c = c | 0x4;
            else if (y < rect.top) c = c | 0x8;
            return c;
        };
        auto clip = [&rect, encode](int& X1, int& Y1, int& X2, int& Y2) -> bool
        {
            int code1, code2, code;
            int x = 0, y = 0;
            code1 = encode(X1, Y1);
            code2 = encode(X2, Y2);
            while (code1 != 0 || code2 != 0)
            {
                if ((code1 & code2) != 0) return false;
                code = code1;
                if (code == 0) code = code2;
                if ((0b1 & code) != 0)
                {
                    x = rect.left;
                    y = Y1 + (Y2 - Y1) * (rect.left - X1) / (X2 - X1);
                }
                else if ((0b10 & code) != 0)
                {
                    x = rect.right;
                    y = Y1 + (Y2 - Y1) * (rect.right - X1) / (X2 - X1);
                }
                else if ((0b100 & code) != 0)
                {
                    y = rect.bottom;
                    x = X1 + (X2 - X1) * (rect.bottom - Y1) / (Y2 - Y1);
                }
                else if ((0b1000 & code) != 0)
                {
                    y = rect.top;
                    x = X1 + (X2 - X1) * (rect.top - Y1) / (Y2 - Y1);
                }
                if (code == code1) 
                {
                    X1 = x;
                    Y1 = y;
                    code1 = encode(x, y);
                }
                else 
                {
                    X2 = x;
                    Y2 = y;
                    code2 = encode(x, y);
                }
            }
            return true;
        };
        if (clip(X1, Y1, X2, Y2))
            DrawLine(X1, Y1, X2, Y2);
    };

    int halfCellWidth = 30 * W;
    int quaterCellWidth = 15 * W;
    int fullCellHeight = 30 * H;
    int halfCellHeight = 15 * H;

    int y1 = Y - 30;
    int x1 = X + 30;

    int x2 = halfCellWidth + X + 30;
    int y2 = quaterCellWidth + y1;

    int x3 = halfCellWidth - fullCellHeight + X + 29;
    int y3 = halfCellHeight + quaterCellWidth + y1 - 1;

    int x4 = X - fullCellHeight + 29;
    int y4 = halfCellHeight + y1 - 1;

    //   1
    //  # #
    // 4   2
    //  # #
    //   3

    ClipAndDrawLine(x1, y1, x2, y2);
    ClipAndDrawLine(x2, y2, x3, y3);
    ClipAndDrawLine(x3, y3, x4, y4);
    ClipAndDrawLine(x4, y4, x1, y1);
    
    // thicker
    if (!bUseDot)
    {
        ClipAndDrawLine(x1 + 1, y1, x2 + 1, y2);
        ClipAndDrawLine(x1 - 1, y1, x2 - 1, y2);
        ClipAndDrawLine(x1 + 2, y1, x2 + 2, y2);
        ClipAndDrawLine(x1 - 2, y1, x2 - 2, y2);

        ClipAndDrawLine(x2 + 1, y2, x3 + 1, y3);
        ClipAndDrawLine(x2 - 1, y2, x3 - 1, y3);
        ClipAndDrawLine(x2 + 2, y2, x3 + 2, y3);
        ClipAndDrawLine(x2 - 2, y2, x3 - 2, y3);

        ClipAndDrawLine(x3 + 1, y3, x4 + 1, y4);
        ClipAndDrawLine(x3 - 1, y3, x4 - 1, y4);
        ClipAndDrawLine(x3 + 2, y3, x4 + 2, y4);
        ClipAndDrawLine(x3 - 2, y3, x4 - 2, y4);

        ClipAndDrawLine(x4 + 1, y4, x1 + 1, y1);
        ClipAndDrawLine(x4 - 1, y4, x1 - 1, y1);
        ClipAndDrawLine(x4 + 2, y4, x1 + 2, y1);
        ClipAndDrawLine(x4 - 2, y4, x1 - 2, y1);
    }

}

void CIsoViewExt::DrawCelltag(int X, int Y)
{
    this->BltToBackBuffer(ImageDataMapHelper::GetImageDataFromMap("CELLTAG")->lpSurface, X, Y, -1, -1);
}

void CIsoViewExt::DrawWaypointFlag(int X, int Y)
{
    this->BltToBackBuffer(ImageDataMapHelper::GetImageDataFromMap("FLAG")->lpSurface, X + 5, Y, -1, -1);
}

void CIsoViewExt::DrawTube(CellData* pData, int X, int Y)
{
    if (auto pTubeData = CMapData::Instance->GetTubeData(pData->Tube))
    {
        auto suffix = pData->TubeDataIndex;
        if (pData->TubeDataIndex >= 2)
            suffix = pTubeData->Directions[pData->TubeDataIndex - 2] + 2;
        FA2sp::Buffer.Format("TUBE%d", suffix);
        if (auto lpSurface = ImageDataMapHelper::GetImageDataFromMap(FA2sp::Buffer)->lpSurface)
            this->BltToBackBuffer(lpSurface, X + 7, Y + 1, -1, -1);
    }
}

BOOL CIsoViewExt::PreTranslateMessageExt(MSG* pMsg)
{
    return CIsoView::PreTranslateMessage(pMsg);
}

BOOL CIsoViewExt::OnMouseWheelExt(UINT Flags, short zDelta, CPoint point)
{
    return TRUE;
}
