#include "FA2sp.h"

#include <ddraw.h>

#include <CINI.h>

#include <GlobalVars.h>

#include <CMapData.h>
#include <CMixFile.h>
#include <CLoading.h>
#include <Drawing.h>
#include <Palette.h>
#include <CIsoView.h>
#include <CFinalSunDlg.h>

#include <unordered_map>

#include "Helpers/Bitmap.h"
#include "Helpers/Screenshot.h"

using DrawDataMap = FAMap<ppmfc::CString, DrawDataStruct, 0x5E7C18, 0>; // DrawDataMap& tmp = *reinterpret_cast<DrawDataMap*>(0x72CBC8);
using SomeDataMap = FAMap<ppmfc::CString, bool, 0x5D8CD0, 0>;

struct SHPImageHeader
{
    short X;
    short Y;
    short Width;
    short Height;
    int compression;
    int unknown;
    int zero;
    int offset;
};

struct ShapeHeaderStruct
{
    short Type;
    short Width;
    short Height;
    short FrameCount;
};

//DEFINE_HOOK(485BE3, ssks, 6)
//{
//    GET(int, v557, ESI);
//    GET(unsigned char**, shapes, EDI);
//
//    REF_STACK(ShapeHeaderStruct, header, STACK_OFFS(0x868, 0x60));
//    Palette* pPal = (Palette*)0x72B4C4;
//
//    for (int k = 0; k < 8; ++k)
//    {
//        bitmap_image bmp;
//        bmp.setwidth_height(header.Width, header.Height, true);
//
//        int count = 0;
//        for (int j = 0; j < bmp.height(); ++j)
//        {
//            for (int i = 0; i < bmp.width(); ++i)
//            {
//                bmp.set_pixel(i, j, pPal->GetByteColor(shapes[k][count]));
//                ++count;
//            }
//        }
//
//        bmp.save_image("test.bmp");
//    }
//    return 0;
//}

//DEFINE_HOOK(483FB7, UseFacing_483FB7, 5)
//{
//    GET_STACK(int, facing, STACK_OFFS(0x874, 0x4C));
//
//    R->Stack(0x0, 4 * facing);
//    Logger::Debug("facing = %d\n", facing);
//
//    return 0;
//}

//DEFINE_HOOK(485D8B, Debug_485DA0, 6)
//{
//    GET(ppmfc::CString*, ppName, EAX);
//    LEA_STACK(DrawDataStruct*, pDrawData, STACK_OFFS(0x868, 0xF8));
//
//    if (pDrawData->FullHeight == 0 || pDrawData->FullWidth == 0)
//        return 0;
//
//    bitmap_image bmp;
//    bmp.setwidth_height(pDrawData->FullWidth, pDrawData->FullHeight, true);
//
//    int count = 0;
//    for (int j = 0; j < bmp.height(); ++j)
//    {
//        for (int i = 0; i < bmp.width(); ++i)
//        {
//            bmp.set_pixel(i, j, pDrawData->pPalette->GetByteColor(pDrawData->pImageBuffer[count]));
//            ++count;
//        }
//    }
//
//    bmp.save_image("test.bmp");
//
//    Logger::Debug("pName = %s\n", *ppName);
//
//    return 0;
//}

//
//DEFINE_HOOK(438DB0, MakeScreenShot, 6)
//{
//    Screenshot("Screenshot.bmp", GlobalVars::Dialogs::CFinalSunDlg->MyViewFrame.pIsoView->lpDDTempBufferSurface);
//
//    return 0x438E4E;
//}

// Replaces search waypoint tool
//DEFINE_HOOK(438DB0, DebugDrawDataMap, 6)
//{
//    SomeDataMap& tmp = *reinterpret_cast<SomeDataMap*>(0x72A870);
//
//    for (auto& x : tmp)
//    {
//        Logger::Debug("%s %d\n", x.first, x.second);
//    }
//
//    return 0x438E4E;
//}

// Replaces search waypoint tool
//DEFINE_HOOK(438DB0, DebugDrawDataMap, 6)
//{
//    DrawDataMap& tmp = *reinterpret_cast<DrawDataMap*>(0x72CBC8);
//
//    for (auto& pair : tmp)
//    {
//        DrawDataStruct& value = pair.second;
//
//        if (pair.first.IsEmpty())
//            continue;
//
//        if (value.Flag == DrawDataFlag::SurfaceData)
//        {
//            if (value.lpSurface)
//            {
//                Screenshot("Exports\\" + pair.first + ".bmp", value.lpSurface);
//            }
//
//        }
//        else
//        {
//            if (pair.second.FullHeight == 0 || pair.second.FullWidth == 0)
//                continue;
//
//            bitmap_image bmp;
//            bmp.setwidth_height(value.FullWidth, value.FullHeight, true);
//
//            int count = 0;
//            for (int j = 0; j < bmp.height(); ++j)
//            {
//                for (int i = 0; i < bmp.width(); ++i)
//                {
//                    bmp.set_pixel(i, j, value.pPalette->GetByteColor(value.pImageBuffer[count]));
//                    ++count;
//                }
//            }
//
//            bmp.save_image((const char*)("Exports\\" + pair.first + ".bmp"));
//        }
//    }
//
//    return 0x438E4E;
//}



//
//struct PalFile
//{
//    struct Color
//    {
//        unsigned char red, green, blue;
//    } Data[256];
//};

//DEFINE_HOOK(5260E0, SHPClass_LoadFrame, 5)
//{
//    GET_STACK(unsigned char*, pData, STACK_OFFS(0x38, -0x4));
//    REF_STACK(SHPImageHeader, header, STACK_OFFS(0x38, 0x18));
//
//    bitmap_image bmp;
//    bmp.setwidth_height(header._cx, header._cy, true);
//    const char* PalName = "unittem.pal";
//    const auto pMix = GlobalVars::Dialogs::CLoading()->SearchFile(PalName);
//    CMixFile::ExtractFile(PalName, PalName, pMix);
//    std::ifstream fin(PalName, std::ios::binary);
//    PalFile pal;
//    fin.read((char*)&pal, sizeof(PalFile));
//    for (auto& entry : pal.Data)
//    {
//        entry.red <<= 2;
//        entry.green <<= 2;
//        entry.blue <<= 2;
//    }
//    fin.close();
//
//    int count = 0;
//    for (int j = 0; j < header._cy; ++j)
//    {
//        for (int i = 0; i < header._cx; ++i)
//        {
//            bmp.set_pixel(i, j, pal.Data[pData[count]]);
//            ++count;
//        }
//    }
//
//    bmp.save_image("test.bmp");
//
//    return 0;
//}
//
//DEFINE_HOOK(4B2610, CMapData_QueryUIName_Debug, 7)
//{
//    /*GET_STACK(const char*, pRegName, 0x4);
//    Logger::Debug(__FUNCTION__" pRegName = %s\n", pRegName);
//    return 0;*/
//
//    static bool asd = true;
//    if (asd)
//    {
//        auto& ini = GlobalVars::INIFiles::CurrentDocument();
//        for (auto& x : ini.Dict)
//        {
//            if (auto name = ini.TryGetString(x.first, "Name"))
//                Logger::Debug("%s %s\n", x.first, name);
//        }
//        asd = false;
//    }
//
//    return 0;
//}

//DEFINE_HOOK(4808A0, CLoading_CreateImage, 5)
//{
//    GET_STACK(CString, pRegName, 0x4);
//    Logger::Debug(__FUNCTION__ " pRegName = %s\n", pRegName);
//    return 0;
//}
//
//Palette* LoadPalette(const char* path, int a2)
//{
//    JMP_STD(0x5273A0);
//}
//
//DEFINE_HOOK(483D7A, CLoading_CreateImage_Palette, 5)
//{
//
//
//    //static std::unordered_map<std::string, Palette*> pals;
//
//    ////GET_STACK(CString, pRegName, STACK_OFFS(0x868, -0x4));
//    //GET(CLoading*, pThis, EDI);
//    //GET_STACK(CString, pSection, STACK_OFFS(0x868, 0x20));
//    //GET_STACK(Palette*, pPalette, STACK_OFFS(0x868, 0x50));
//    ////Logger::Debug(__FUNCTION__ " pRegName = %s\n", pSection);
//    //
//    //auto& art = GlobalVars::INIFiles::Art();
//    //CString palname = art.GetString(pSection, "Palette");
//    //
//    //bool hasext = false;
//    //if (palname.IsEmpty())
//    //{
//    //    palname = art.GetString(pSection, "CustomPalette");
//    //    if (palname.IsEmpty())
//    //        return 0x483DCE;
//    //    hasext = true;
//    //}
//
//    //if (!hasext)
//    //    palname += ".pal";
//
//    //if (pals.find(palname.operator LPCTSTR()) == pals.end())
//    //{
//    //    CString path;
//    //    path = GlobalVars::ExePath();
//    //    path += palname;
//    //    auto const pMix = GlobalVars::Dialogs::CLoading()->SearchFile(palname);
//    //    if (!CMixFile::ExtractFile(palname, path, pMix))
//    //        return 0x483DCE;
//    //    auto pPal = LoadPalette(path, 0);
//    //    DeleteFile(path);
//    //    pals[palname.operator LPCTSTR()] = pPal;
//    //}
//
//    //pPalette = pals[palname.operator LPCTSTR()];
//
//    CString path = GlobalVars::ExePath();
//    path += "\\TmpPalette.pal";
//    CMixFile::ExtractFile("_ID2124019542", "", GlobalVars::Dialogs::CLoading()->MIX_CACHE);
//
//    return 0x483DCE;
//}

//
//DEFINE_HOOK(4943BE, Hook_494350, 5)
//{
//    struct CSFThingA
//    {
//        CString Source;
//        wchar_t* WideString;
//        int Unknown;
//        int Length;
//    };
//
//
//    GET(CSFThingA*, pThis, ESI);
//    GET_STACK(char*, lpString, STACK_OFFS(0x1C, -0x4));
//
//    Logger::Debug("%s\n", lpString);
//    
//
//    return 0;
//}

//DEFINE_HOOK(526020, ShapeFileClass_Draw, 8)
//{
//    GET_STACK(int, nFrame, 0x4);
//    GET_STACK(UINT, nFlags, 0x8);
//    GET_STACK(int, what, 0xC);
//
//    Logger::Debug(__FUNCTION__" nFrame = %d, nFlag = %d, what = %08X\n", nFrame, nFlags, what);
//
//    return 0;
//}

//DEFINE_HOOK(4B5D98, Debug_4AE910_Begin, 5)
//{
//    GET(const char*, pRegName, EAX);
//    if(pRegName)
//        Logger::Debug(__FUNCTION__" pRegName = %s\n", pRegName);
//    return 0;
//}
//
//DEFINE_HOOK(4B5DA3, Debug_4AE910_End, 8)
//{
//    GET(int, nResult, EAX);
//    Logger::Debug(__FUNCTION__" nResult = %d\n", nResult);
//    return 0;
//}
//
//DEFINE_HOOK(483669, Building_SHPTurret_SectionNameFix, 5)
//{
//    //GET_STACK(const char**, pSectionName, STACK_OFFS(0x86C, 0x90));
//    GET(const char**, pSectionName, ECX);
//    Logger::Debug(__FUNCTION__" DEBUGGING %s\n", *pSectionName);
//    return 0;
//}
//DEFINE_HOOK(531D33, Debug_531D33_FileName, 8)
//{
//    GET(const char*, pFileName, EAX);
//    Logger::Debug(__FUNCTION__" Filename = %s\n", pFileName);
//    return 0;
//}


/*
* The SHPDict is used for two different places.
* First one is the smudges. Which will be called during the map initialization.
* Then the x.second means the order of the smudge loading
* 
* The second one is for the Technotypes.
* 
* [Debug] sub_4767B0 pStr = KNIGHT
* [Debug] Current map details:
* [Debug] ADOG - 1
* [Debug] BPLN - 1
* [Debug] E1 - 1
* [Debug] ETNK - 0
* [Debug] GACNST - 0
* [Debug] GAPILE - 0
* [Debug] GGI - 1
* [Debug] KNIGHT - 0
* [Debug] NACNST - 0
* [Debug] NAHAND - 0
* [Debug] NAWEAP - 0
* [Debug] ORCA - 1
* [Debug] PDPLANEUS - 1
* [Debug] TENGU - 0
* 
* I cannot find out wtf it is though currently.
* 
 */
//DEFINE_HOOK(4767F8, sub_4767B0, 8)
//{
//    using SHPDict = FAMap<ppmfc::CString, DWORD, 0x5D8CD0, 0x5D8CCC>;
//
//    GET(SHPDict*, pDict, ESI);
//    GET_STACK(CString*, pStr, 0x20 + 0x4);
//
//    Logger::Debug(__FUNCTION__" pStr = %s\n", *pStr);
//    Logger::Debug("Current map details:\n");
//    for (auto& x : *pDict)
//        Logger::Debug("%s - %d\n", x.first, x.second);
//    Logger::Debug("\n");
//
//    return 0;
//}

