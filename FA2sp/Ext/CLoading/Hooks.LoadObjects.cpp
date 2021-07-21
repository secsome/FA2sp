#include "Body.h"

#include <Helpers/Macro.h>

#include <CObjectDatas.h>

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

    switch (dwCaller)
    {
    case 0x473E63: // Infantry
    case 0x4737DA: // Aircraft
    case 0x4731AD: // Unit
    case 0x4730EA:
        new(pRet) ppmfc::CString(CLoadingExt::GetImageName(ID, nFacing));
        return 0x47623D;
    default:
        return 0;
    }
}

DEFINE_HOOK(47319F, GetObjectName_Unit_StringFix_1, 7)
{
    LEA_STACK(ppmfc::CString*, pRet, STACK_OFFS(0xD1C, 0xCB4));
    R->EDX(pRet);
    return 0x4731A6;
}

DEFINE_HOOK(4731B0, GetObjectName_Unit_StringFix_2, 5)
{
    return 0x4731D6;
}

//
//DEFINE_HOOK(4768D0, SADASFVJHB, 7)
//{
//    GET_STACK(ppmfc::CString*, ppStr, 0x4);
//
//    Logger::Debug("%s\n", *ppStr);
//
//    return 0;
//}