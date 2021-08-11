#pragma once

#include "../FA2sp.h"

#include <MFC/ppmfc_cstring.h>

class DrawStuff
{
public:
    static void init();
    static void deinit();
    static bool load_vpl(ppmfc::CString name);
    static bool load_vxl(ppmfc::CString name);
    static bool load_hva(ppmfc::CString name);
    static bool get_to_image(unsigned int nFacing, unsigned char*& pBuffer, int& width, int& height, const int offset = 0);
    static bool get_to_image(unsigned int nFacing, unsigned char*& pBuffer, int& width, int& height, int& x, int& y, const int offset = 0);
    static bool is_vpl_loaded();
};