#include "VoxelDrawer.h"

#include <CLoading.h>

void VoxelDrawer::Initalize()
{
    CncImgCreate();
    CncImgSetMaxFacing(32);
}

void VoxelDrawer::Finalize()
{
    CncImgRelease();
}

bool VoxelDrawer::LoadVPLFile(ppmfc::CString name)
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

bool VoxelDrawer::LoadVXLFile(ppmfc::CString name)
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

bool VoxelDrawer::LoadHVAFile(ppmfc::CString name)
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

bool VoxelDrawer::GetImageData(unsigned int nFacing, unsigned char*& pBuffer, int& width,
    int& height, int& x, int& y, const int F, const int L, const int H)
{
    const unsigned int nIndex = nFacing * 4;
    CncImgPrepareVXLCache(nIndex, F, L, H);
    CncImgGetImageFrame(nIndex, &width, &height, &x, &y);
    if (width < 0 || height < 0)
        return false;
    return CncImgGetImageData(nIndex, &pBuffer);
}

bool VoxelDrawer::GetImageData(unsigned int nFacing, unsigned char*& pBuffer, VoxelRectangle& rect, const int F, const int L, const int H)
{
    return GetImageData(nFacing, pBuffer, rect.W, rect.H, rect.X, rect.Y, F, L, H);
}

bool VoxelDrawer::IsVPLLoaded()
{
    return CncImgIsVPLLoaded();
}
