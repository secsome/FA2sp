#pragma once

namespace thomas {
    class vxlfile;
    class vplfile;
}

class vxl_drawing_lib
{
public:
    static thomas::vxlfile* global_vxl;
    static thomas::vplfile* global_vpl;

    static void init();
    static void deinit();
    static bool load_vpl(unsigned char* pVPLBuffer);
    static bool load_vxl(unsigned char* pVXLBuffer);
    static bool load_hva(unsigned char* pHVABuffer);
    static bool prepare_cache(unsigned int nFacing, const int F, const int L, const int H);
    static int get_image_width(unsigned int nFacing);
    static int get_image_height(unsigned int nFacing);
    static void get_image_frame(unsigned int nFacing, int& width, int& height, int& x, int& y);
    static void get_image_size(unsigned int nFacing, int& width, int& height);
    static bool get_to_image(unsigned int nFacing, unsigned char*& pBuffer);
    static void clear();
    static bool is_loaded();
    static bool is_vpl_loaded();
};