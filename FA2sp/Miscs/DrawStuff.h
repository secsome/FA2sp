#pragma once

#include "../FA2sp.h"
#include "../CncVxlRenderText.h"

#include <MFC/ppmfc_cstring.h>

class DrawStuff
{
public:
    static void init();
    static void deinit();
    static bool load_vpl(ppmfc::CString name);
    static bool load_vxl(ppmfc::CString name);
    static bool load_hva(ppmfc::CString name);
    static bool get_to_image(unsigned int nFacing, unsigned char*& pBuffer, 
        int& width, int& height, int& x, int& y, const int F = 0, const int L = 0, const int H = 0);
    static bool is_vpl_loaded();
};