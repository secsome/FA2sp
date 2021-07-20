#include "Body.h"

#include <Helpers/Macro.h>

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
    GET_STACK(ppmfc::CString, ID, 0x8);
    GET_STACK(int, nFacing, 0xC);
    GET_STACK(DWORD, dwCaller, 0x0);


    if (dwCaller == 0x473E63)
    {
        new(pRet) ppmfc::CString(CLoadingExt::GetImageName(ID, nFacing));
        return 0x47623D;
    }

    return 0;
}

DEFINE_HOOK(4768D0, SADASFVJHB, 7)
{
    GET_STACK(ppmfc::CString*, ppStr, 0x4);

    Logger::Debug("%s\n", *ppStr);

    return 0;
}