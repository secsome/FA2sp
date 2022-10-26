#include "DrawStuff.h"

#include <CLoading.h>

void DrawStuff::init()
{
    CncImgCreate();
}

void DrawStuff::deinit()
{
    CncImgRelease();
}

bool DrawStuff::load_vpl(ppmfc::CString name)
{
    bool result = false;
    DWORD dwSize;
    if (auto pBuffer = (unsigned char*)CLoading::Instance->ReadWholeFile(name, &dwSize))
    {
        result = CncImgLoadVPLFile(pBuffer);
        GameDeleteArray(pBuffer, dwSize);
    }
    return result;
}

bool DrawStuff::load_vxl(ppmfc::CString name)
{
    bool result = false;
    DWORD dwSize;
    if (auto pBuffer = (unsigned char*)CLoading::Instance->ReadWholeFile(name, &dwSize))
    {
        if (CncImgIsVXLLoaded())
            CncImgClearCurrentVXL();
        result = CncImgLoadVXLFile(pBuffer);
        GameDeleteArray(pBuffer, dwSize);
    }
    return result;
}

bool DrawStuff::load_hva(ppmfc::CString name)
{
    bool result = false;
    DWORD dwSize;
    if (auto pBuffer = (unsigned char*)CLoading::Instance->ReadWholeFile(name, &dwSize))
    {
        result = CncImgLoadHVAFile(pBuffer);
        GameDeleteArray(pBuffer, dwSize);
    }
    return result;
}

bool DrawStuff::get_to_image(unsigned int nFacing, unsigned char*& pBuffer, int& width,
    int& height, int& x, int& y, const int F, const int L, const int H)
{
    unsigned int nIndex = 4 * nFacing;
    CncImgPrepareVXLCache(nIndex, F, L, H);
    CncImgGetImageFrame(nIndex, &width, &height, &x, &y);
    if (width < 0 || height < 0)
        return false;
    return CncImgGetImageData(nIndex, &pBuffer);
}

bool DrawStuff::is_vpl_loaded()
{
    return CncImgIsVPLLoaded();
}
