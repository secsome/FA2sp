#include "Body.h"

#include "../../FA2sp.h"

#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>

#include <WindowsX.h>
#include <CPalette.h>
#include <CTileTypeClass.h>

#include <CMapData.h>
#include <Drawing.h>
#include <CINI.h>

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

void CIsoViewExt::OnDraw()
{
    if (CMapData::MapNotLoaded)
        return;

    if (OverlayData::LastOverlayData)
    {
        OverlayData::LastOverlayData = nullptr;
        return;
    }

    CFinalSunDlg::LastSucceededOperation = 100;
    CMapData::Instance->UpdateCurrentDocument();

    if (!this->lpDDPrimarySurface)
        return;

    if (this->IsInitializing || !CTileTypeClass::Instance || !*CTileTypeClass::Instance || !*CTileTypeClass::InstanceCount)
        return;

    if (this->lpDDPrimarySurface->IsLost())
    {
        this->PrimarySurfaceLost();
        return;
    }

    if (!CMapData::Instance->MapWidthPlusHeight)
        return;

    DDBLTFX ddBltfx;
    ZeroMemory(&ddBltfx, sizeof(ddBltfx));
    ddBltfx.dwSize = sizeof(ddBltfx);
    ddBltfx.dwFillColor = 0xFFFFFF;
    this->lpDDBackBufferSurface->Blt(nullptr, nullptr, nullptr, DDBLT_COLORFILL, &ddBltfx);

    RECT windowRect, clientRect;
    this->GetWindowRect(&windowRect);
    this->GetClientRect(&clientRect);

    auto dX = this->ViewPosition.x - windowRect.left * ONE_SIXTH;
    auto dY = this->ViewPosition.y - windowRect.top * ONE_THIRD;

    RECT fullRect
    {
        clientRect.right + dX,
        clientRect.top + dY,
        windowRect.left + dX,
        windowRect.bottom + dY
    };

    int Coord_X, Coord_Y;

    this->CalculateViewBounds(fullRect.left, fullRect.top, Coord_X, Coord_Y);
    this->CalculateViewBounds(fullRect.right, fullRect.bottom, Coord_X, Coord_Y);

    int _right = Coord_X;
    int _left = fullRect.left;
    fullRect.right = windowRect.left + clientRect.right + dX;
    fullRect.bottom = clientRect.bottom + windowRect.top + dY;
    fullRect.top = clientRect.top + dY;
    fullRect.left = clientRect.left + dX;

    this->CalculateViewBounds(fullRect.left, fullRect.top, Coord_X, Coord_Y);
    this->CalculateViewBounds(fullRect.right, fullRect.bottom, Coord_X, Coord_Y);

    RECT finalRect{ _left - 2,fullRect.top - 2,_right + 2,fullRect.bottom + 2 };
    if (finalRect.left < 0)
        finalRect.left = 0;
    if (finalRect.top < 0)
        finalRect.top = 0;
    if (finalRect.right > CMapData::Instance->MapWidthPlusHeight || finalRect.right < finalRect.left)
        finalRect.right = CMapData::Instance->MapWidthPlusHeight;
    if (finalRect.bottom > CMapData::Instance->MapWidthPlusHeight || finalRect.bottom < finalRect.top)
        finalRect.bottom = CMapData::Instance->MapWidthPlusHeight;

    int nHeightBase = CINI::CurrentTheater->GetInteger("General", "HeightBase");
    int nHeightData = CMapData::Instance->HeightDatas[nHeightBase];
    
    int nMapWidth = CMapData::Instance->Size.right;
    int nMapHeight = CMapData::Instance->Size.bottom;

    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT;

    this->lpDDBackBufferSurface->GetSurfaceDesc(&ddsd);
    this->lpDDBackBufferSurface->Lock(nullptr, &ddsd, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL);
    
    for (int i = finalRect.left; i < finalRect.right; ++i)
    {
        for (int j = finalRect.top; j < finalRect.bottom; ++j)
        {
            auto pCell = CMapData::Instance->TryGetCellAt(j, i);
            int X = i, Y = j;
            if (CFinalSunApp::Instance->FlatToGround)
                this->MapCoord2ScreenCoord_Flat(X, Y);
            else
                this->MapCoord2ScreenCoord_Height(X, Y);
            
            X -= dX;
            Y -= dY;

            Y -= 49;

            // Now (X, Y) is just the center of a cell

            if (pCell->CellTag != -1)
            {
                this->DrawCelltag(X, Y);
                BGRStruct ddColor;
                ddColor.R = 0;
                ddColor.G = 0;
                ddColor.B = 0xFF;

                if (X > 0 && X < ddsd.dwWidth && Y > 0 && Y < ddsd.dwHeight)
                {
                    auto ptr = (unsigned char*)ddsd.lpSurface + ddsd.lPitch * Y + X * *(int*)0x72A8C0;
                    memcpy(ptr, &ddColor, *(int*)0x72A8C0);
                }

                this->DrawLockedCellOutline(X - 30, Y + 15, 1, 1, 0xFF, false, false, &ddsd);
            }
        }
    }
    
    this->lpDDBackBufferSurface->Unlock(nullptr);
    this->lpDDTempBufferSurface->Blt(nullptr, this->lpDDBackBufferSurface, nullptr, NULL, nullptr);

    this->lpDD7->WaitForVerticalBlank(DDWAITVB_BLOCKEND, NULL);
    this->lpDDPrimarySurface->Blt(nullptr, this->lpDDBackBufferSurface, nullptr, NULL, nullptr);

    CFinalSunDlg::LastSucceededOperation = 10100;
}

void CIsoViewExt::CalculateViewBounds(LONG& rect_X, LONG& rect_Y, int& Coord_X, int& Coord_Y)
{
    Coord_X = rect_X;
    Coord_Y = rect_Y;
    this->ScreenCoord2MapCoord(Coord_X, Coord_Y);

    bool exit = false;
    for (int k = 15; k > 0 && exit; --k)
    {
        for (int i = 0; i < 3; ++i)
        {
            int a = k + Coord_X;
            int b = k + Coord_Y;
            if (i == 1)
                --a;
            else if (i == 2)
                --b;

            int aa = a;
            int bb = b;
            if (a >= 0 && b >= 0 && a < CMapData::Instance->MapWidthPlusHeight && b < CMapData::Instance->MapWidthPlusHeight)
            {
                auto pCellData = CMapData::Instance->TryGetCellAt(b, a);
                this->MapCoord2ScreenCoord_Height(a, b);

                auto c = rect_X - a;
                auto d = rect_Y - b - 15;

                auto e = c * ONE_SIXTH;
                auto f = d * ONE_THIRD;

                if (!(f - e + 1) && !(e + f) || !CFinalSunDlg::ControlKeyIsDown && rect_Y - b > 30)
                {
                    rect_X = aa;
                    rect_Y = bb;
                    exit = true;
                    break;
                }
            }
        }
    }
    if (!exit)
    {
        rect_X = Coord_X;
        rect_Y = Coord_Y;
    }
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
            if (x < rect.left) c = c | 0b1;
            else if (x > rect.right) c = c | 0b10;
            if (y > rect.bottom) c = c | 0b100;
            else if (y < rect.top) c = c | 0b1000;
            return c;
        };
        auto clip = [&rect, encode](int& X1, int& Y1, int& X2, int& Y2) -> bool
        {
            int code1, code2, code;
            int x, y;
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

void CIsoViewExt::DrawWaypoint(int WPIndex, int X, int Y)
{
    this->BltToBackBuffer(ImageDataMapHelper::GetImageDataFromMap("FLAG")->lpSurface, X, Y - 2, -1, -1);
    if (auto pSection = CINI::CurrentDocument->GetSection("Waypoints"))
        this->DrawText(X + 15, Y + 7, *pSection->GetKeyAt(WPIndex), ExtConfigs::Waypoint_Color);
}

void CIsoViewExt::DrawTube(CellData* pData, int X, int Y)
{
    if (auto pTubeData = CMapData::Instance->GetTubeData(pData->Tube))
    {
        auto suffix = pData->TubeDataIndex;
        if (pData->TubeDataIndex >= 2)
            suffix = pTubeData->Data[pData->TubeDataIndex] + 2;
        FA2sp::Buffer.Format("TUBE%d", suffix);
        if (auto lpSurface = ImageDataMapHelper::GetImageDataFromMap(FA2sp::Buffer)->lpSurface)
            this->BltToBackBuffer(lpSurface, X + 7, Y + 1, -1, -1);
    }
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
