#pragma once

#include "../FA2sp.h"
#include "../CncVxlRenderText.h"

#include <MFC/ppmfc_cstring.h>

struct VoxelRectangle
{
    int X, Y, W, H;
};

class VoxelDrawer
{
public:
    static void Initalize();
    static void Finalize();
    static bool LoadVPLFile(ppmfc::CString name);
    static bool LoadVXLFile(ppmfc::CString name);
    static bool LoadHVAFile(ppmfc::CString name);
    static bool GetImageData(unsigned int nFacing, unsigned char*& pBuffer, 
        int& width, int& height, int& x, int& y, const int F = 0, const int L = 0, const int H = 0);
    static bool GetImageData(unsigned int nFacing, unsigned char*& pBuffer,
        VoxelRectangle& rect, const int F = 0, const int L = 0, const int H = 0);
    static bool IsVPLLoaded();
};