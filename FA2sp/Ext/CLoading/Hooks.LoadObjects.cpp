#include "Body.h"

#include <Helpers/Macro.h>

#include <CObjectDatas.h>
#include <GlobalVars.h>
#include <CINI.h>

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

//DEFINE_HOOK(471162, CIsoView_Draw_PowerUp1Loc, 5)
//{
//    REF_STACK(const ppmfc::CString, ID, STACK_OFFS(0xD18, 0xBFC));
//    GET_STACK(const int, X, STACK_OFFS(0xD18, 0xCFC));
//    GET_STACK(const int, Y, STACK_OFFS(0xD18, 0xD00));
//    
//    if (auto ppBld = Variables::Rules.TryGetString(ID, "PowersUpBuilding"))
//    {
//        ppmfc::CString ArtID;
//        if (auto ppImage = Variables::Rules.TryGetString(*ppBld, "Image"))
//            ArtID = *ppImage;
//        else
//            ArtID = *ppBld;
//        R->ESI(X + GlobalVars::INIFiles::Art->GetInteger(ArtID, "PowerUp1LocXX", 0));
//        R->EDI(Y + GlobalVars::INIFiles::Art->GetInteger(ArtID, "PowerUp1LocYY", 0));
//    }
//    else
//    {
//        R->ESI(X);
//        R->EDI(Y);
//    }
//
//    return 0x47141D;
//}