#include "Body.h"

#include <Helpers/Macro.h>

#include <CMapData.h>
#include <CObjectDatas.h>
#include <CINI.h>
#include <Drawing.h>

#include "../../FA2sp.h"


DEFINE_HOOK(4808A0, CLoading_LoadObjects, 5)
{
    GET(CLoadingExt*, pThis, ECX);
    REF_STACK(ppmfc::CString, pRegName, 0x4);

    pThis->CLoadingExt::LoadObjects(pRegName);

    return 0x486173;
}

DEFINE_HOOK(475450, GetObjectName, 7)
{
    GET_STACK(ppmfc::CString*, pRet, 0x4);
    GET_STACK(LPCSTR, ID, 0x8);
    GET_STACK(int, nFacing, 0xC);
    GET_STACK(DWORD, dwCaller, 0x0);

    const ppmfc::CString temp = CLoadingExt::GetImageName(ID, nFacing);

    switch (dwCaller)
    {
    case 0x473E63: // Infantry
    case 0x4737DA: // Aircraft
    case 0x4731AD: // Unit
    case 0x4730EA:
    case 0x4B5DF6: // Building
    case 0x4B607D:
    case 0x4B67A0:
    case 0x4B67C3:
    case 0x4B6C02:
    case 0x4B6C30:
    case 0x470EA1: // Powerups
    case 0x471036:
    case 0x4716C9:
    case 0x47187A:
    case 0x471E64:
    case 0x471FCD:
        new(pRet) ppmfc::CString(temp);
        R->EAX(pRet);
        return 0x47623D;
    default:
        return 0;
    }
}

DEFINE_HOOK_AGAIN(471028, CLoading_Draw_PowerUpFacingFix, 7)
DEFINE_HOOK_AGAIN(470E93, CLoading_Draw_PowerUpFacingFix, 7)
DEFINE_HOOK_AGAIN(471FBF, CLoading_Draw_PowerUpFacingFix, 7)
DEFINE_HOOK_AGAIN(471E56, CLoading_Draw_PowerUpFacingFix, 7)
DEFINE_HOOK_AGAIN(47186C, CLoading_Draw_PowerUpFacingFix, 7)
DEFINE_HOOK(4716BB, CLoading_Draw_PowerUpFacingFix, 7)
{
    R->Stack(0, 0);
    return 0;
}

DEFINE_HOOK(42CBFC, CFinalSunDlg_CreateMap_ClearCLoadingExtData, 8)
{
    CLoadingExt::ClearItemTypes();
    return 0;
}

DEFINE_HOOK(49D2C0, CMapData_LoadMap_ClearCLoadingExtData, 5)
{
    CLoadingExt::ClearItemTypes();
    return 0;
}

DEFINE_HOOK(49D5CC, CLoading_LoadMap_CallMissingRelease, 5)
{
    GET(CLoading*, pThis, ESI);

    pThis->Release();
    pThis->InitializeDDraw();

    return 0;
}

DEFINE_HOOK(491FD4, CLoading_Release_SetImageDataToNullptr, 5)
{
    GET(char*, pNode, ESI); // Map node in fact
    ImageDataClass* pData = (ImageDataClass*)(pNode + 0xC + 0x4); // data = pNode->_Value.second
    
    if (pData->pImageBuffer)
    {
        GameDelete(pData->pImageBuffer);
        pData->pImageBuffer = nullptr;
    }
    if (pData->pPixelValidRanges)
    {
        GameDelete(pData->pPixelValidRanges);
        pData->pPixelValidRanges = nullptr;
    }

    return 0x491FF1;
}