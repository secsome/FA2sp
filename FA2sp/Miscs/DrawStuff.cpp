#include "DrawStuff.h"

#include <GlobalVars.h>
#include <CLoading.h>

#include "../vxl_drawing_lib.h"

void DrawStuff::init()
{
    vxl_drawing_lib::init();
}

void DrawStuff::deinit()
{
    vxl_drawing_lib::deinit();
}

bool DrawStuff::load_vpl(ppmfc::CString name)
{
    bool result = false;
    if (auto pBuffer = (unsigned char*)GlobalVars::Dialogs::CLoading->ReadWholeFile(name))
    {
        result = vxl_drawing_lib::load_vpl(pBuffer);
        GameDelete(pBuffer);
    }
    return result;
}

bool DrawStuff::load_vxl(ppmfc::CString name)
{
    bool result = false;
    if (auto pBuffer = (unsigned char*)GlobalVars::Dialogs::CLoading->ReadWholeFile(name))
    {
        if (vxl_drawing_lib::is_loaded())
            vxl_drawing_lib::clear();
        result = vxl_drawing_lib::load_vxl(pBuffer);
        GameDelete(pBuffer);
    }
    return result;
}

bool DrawStuff::load_hva(ppmfc::CString name)
{
    bool result = false;
    if (auto pBuffer = (unsigned char*)GlobalVars::Dialogs::CLoading->ReadWholeFile(name))
    {
        result = vxl_drawing_lib::load_hva(pBuffer);
        GameDelete(pBuffer);
    }
    return result;
}

bool DrawStuff::get_to_image(unsigned int nFacing, unsigned char*& pBuffer,int& width, int& height)
{
    unsigned int nIndex = 4 * nFacing;
    vxl_drawing_lib::prepare_cache(nIndex);
    vxl_drawing_lib::get_image_size(nIndex, width, height);
    if (width < 0 || height < 0)
        return false;
    pBuffer = GameCreateArray<unsigned char>(width * height);
    return vxl_drawing_lib::get_to_image(nIndex, pBuffer);
}

bool DrawStuff::get_to_image(unsigned int nFacing, unsigned char*& pBuffer, int& width, int& height, int& x, int& y)
{
    unsigned int nIndex = 4 * nFacing;
    vxl_drawing_lib::prepare_cache(nIndex);
    vxl_drawing_lib::get_image_frame(nIndex, width, height, x, y);
    if (width < 0 || height < 0)
        return false;
    pBuffer = GameCreateArray<unsigned char>(width * height);
    return vxl_drawing_lib::get_to_image(nIndex, pBuffer);
}

bool DrawStuff::is_vpl_loaded()
{
    return vxl_drawing_lib::is_vpl_loaded();
}