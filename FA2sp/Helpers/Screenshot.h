#pragma once
//---------------------------------------------------------------------------
//
//    Screenshot - Author: Michael Fötsch; Date: May 31, 2000
//
//---------------------------------------------------------------------------

#include <ddraw.h>
#include <math.h>
//---------------------------------------------------------------------------
// Helper function to retrieve current position of file pointer:
inline int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}
//---------------------------------------------------------------------------

// Helper macro to return from function when error occurs:
#define ERROR_BREAK(x) throw (int)(x);

// Screenshot
//    -> FileName: Name of file to save screenshot to
//    -> lpDDS: DirectDraw surface to capture
//    <- Result: Success
//
bool Screenshot(LPCTSTR FileName, LPDIRECTDRAWSURFACE7 lpDDS)
{
    if (!FileName || !lpDDS) return false;
    bool Success = false;
    HDC SurfDC = NULL;        // GDI-compatible device context for the surface
    HBITMAP OffscrBmp = NULL; // bitmap that is converted to a DIB
    HDC OffscrDC = NULL;      // offscreen DC that we can select OffscrBmp into
    LPBITMAPINFO lpbi = NULL; // bitmap format info; used by GetDIBits
    LPVOID lpvBits = NULL;    // pointer to bitmap bits array
    HANDLE BmpFile = INVALID_HANDLE_VALUE;    // destination .bmp file
    BITMAPFILEHEADER bmfh;  // .bmp file header
    try
    {
        // Get dimensions of Surface:
        DDSURFACEDESC2 ddsd;
        ZeroMemory(&ddsd, sizeof(ddsd));
        ddsd.dwSize = sizeof(ddsd);
        if (FAILED(lpDDS->GetSurfaceDesc(&ddsd))) ERROR_BREAK(0);
        int Width = ddsd.dwWidth;
        int Height = ddsd.dwHeight;

        // Create a GDI-compatible device context for the surface:
        if (FAILED(lpDDS->GetDC(&SurfDC))) ERROR_BREAK(1);

        // We need an HBITMAP to convert it to a DIB:
        if ((OffscrBmp = CreateCompatibleBitmap(SurfDC, Width, Height)) == NULL)
            ERROR_BREAK(2);



        // The bitmap is empty, so let's copy the contents of the surface to it.
        // For that we need to select it into a device context. We create one.
        if ((OffscrDC = CreateCompatibleDC(SurfDC)) == NULL) ERROR_BREAK(3);

        // Select OffscrBmp into OffscrDC:
        HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);

        // Now we can copy the contents of the surface to the offscreen bitmap:
        BitBlt(OffscrDC, 0, 0, Width, Height, SurfDC, 0, 0, SRCCOPY);

        // We don't need SurfDC anymore. Free it:
        lpDDS->ReleaseDC(SurfDC); SurfDC = NULL;

        // GetDIBits requires format info about the bitmap. We can have GetDIBits
        // fill a structure with that info if we pass a NULL pointer for lpvBits:
        // Reserve memory for bitmap info (BITMAPINFOHEADER + largest possible
        // palette):
        if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL) 
            ERROR_BREAK(4);
        ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
        lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

        // Get info but first de-select OffscrBmp because GetDIBits requires it:
        SelectObject(OffscrDC, OldBmp);
        if (!GetDIBits(OffscrDC, OffscrBmp, 0, Height, NULL, lpbi, DIB_RGB_COLORS))
            ERROR_BREAK(5);

        // Reserve memory for bitmap bits:
        if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
            ERROR_BREAK(6);

        // Have GetDIBits convert OffscrBmp to a DIB (device-independent bitmap):
        if (!GetDIBits(OffscrDC, OffscrBmp, 0, Height, lpvBits, lpbi, DIB_RGB_COLORS)) 
            ERROR_BREAK(7);

        // Create a file to save the DIB to:
        if ((BmpFile = CreateFile(FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
            ERROR_BREAK(8);

        DWORD Written;    // number of bytes written by WriteFile
        // Write a file header to the file:
        bmfh.bfType = 19778;        // 'BM'
        // bmfh.bfSize = ???        // we'll write that later
        bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
        // bmfh.bfOffBits = ???     // we'll write that later
        if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
            ERROR_BREAK(9);

        if (Written < sizeof(bmfh)) ERROR_BREAK(9);

        // Write BITMAPINFOHEADER to the file:
        if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER),&Written, NULL)) 
            ERROR_BREAK(10);

        if (Written < sizeof(BITMAPINFOHEADER)) ERROR_BREAK(10);

        // Calculate size of palette:
        int PalEntries;

        // 16-bit or 32-bit bitmaps require bit masks:
        if (lpbi->bmiHeader.biCompression == BI_BITFIELDS) 
            PalEntries = 3;
        else
            // bitmap is palettized?
            PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
            // 2^biBitCount palette entries max.:
            (int)(1 << lpbi->bmiHeader.biBitCount)
            // bitmap is TrueColor -> no palette:
            : 0;

        // If biClrUsed use only biClrUsed palette entries:
        if (lpbi->bmiHeader.biClrUsed) 
            PalEntries = lpbi->bmiHeader.biClrUsed;

        // Write palette to the file:
        if (PalEntries)
        {
            if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL)) ERROR_BREAK(11);
            if (Written < PalEntries * sizeof(RGBQUAD)) ERROR_BREAK(11);
        }

        // The current position in the file (at the beginning of the bitmap bits)
        // will be saved to the BITMAPFILEHEADER:
        bmfh.bfOffBits = GetFilePointer(BmpFile);

        // Write bitmap bits to the file:
        if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL)) ERROR_BREAK(12);
        if (Written < lpbi->bmiHeader.biSizeImage) ERROR_BREAK(12);

        // The current pos. in the file is the final file size and will be saved:
        bmfh.bfSize = GetFilePointer(BmpFile);

        // We have all the info for the file header. Save the updated version:
        SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
        if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
            ERROR_BREAK(13);
        if (Written < sizeof(bmfh)) ERROR_BREAK(13);
        Success = true;
    }
    catch (int& errorcode)
    {
        char Buf[100];
        wsprintf(Buf, "Screenshot error #%i", errorcode);
        OutputDebugString(Buf);
    }
    catch (...)
    {
        OutputDebugString("Screenshot error");
    }
    if (SurfDC) lpDDS->ReleaseDC(SurfDC);
    if (OffscrDC) DeleteDC(OffscrDC);
    if (OffscrBmp) DeleteObject(OffscrBmp);
    if (lpbi) delete[] lpbi;
    if (lpvBits) delete[] lpvBits;
    if (BmpFile != INVALID_HANDLE_VALUE) CloseHandle(BmpFile);

    return Success;
}