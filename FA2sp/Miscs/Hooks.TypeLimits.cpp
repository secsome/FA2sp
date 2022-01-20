//#include <Helpers/Macro.h>
//
//#include <Drawing.h>
//
//#include "../RunTime.h"
//
//static constexpr size_t BuildingTypeLimit = 10000; // FA2 defaults to 3840
//
//static char BuildingDatas[BuildingTypeLimit * sizeof(BuildingData)];
//
//// No need to construct vanilla data now
//DEFINE_HOOK(519300, BuildingTypeDatas_DynamicCTOR, 5)
//{
//    return 0x519329;
//}
//
//DEFINE_HOOK(519330, BuildingTypeDatas_DynamicDTOR, 5)
//{
//    return 0x519349;
//}
//
//DEFINE_HOOK(537129, ExeRun_BuildingTypeLimit, 9)
//{
//    auto ReplaceImage = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, (void*)BuildingDatas);
//    };
//    auto ReplaceWidth = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->Foundation_Width);
//    };
//    auto ReplaceHeight = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->Foundation_Height);
//    };
//    auto ReplaceTemperateFlag = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->AllowToPlaceInTemperate);
//    };
//    auto ReplaceSnowFlag = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->AllowToPlaceInSnow);
//    };
//    auto ReplaceUrbanFlag = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->AllowToPlaceInUrban);
//    };
//    auto ReplaceFacingCount = [](unsigned long addr)
//    {
//        RunTime::ResetMemoryContentAt(addr, &((BuildingData*)BuildingDatas)->FacingCount);
//    };
//    
//    RunTime::ResetMemoryContentAt(0x470956, BuildingTypeLimit);
//    RunTime::ResetMemoryContentAt(0x4727C1, BuildingTypeLimit);
//    RunTime::ResetMemoryContentAt(0x4B6BC9, BuildingTypeLimit);
//    RunTime::ResetMemoryContentAt(0x4B5DAC, BuildingTypeLimit);
//    RunTime::ResetMemoryContentAt(0x4B6755, BuildingTypeLimit);
//
//    ReplaceImage(0x4709B9);
//    ReplaceImage(0x4709D0);
//    ReplaceImage(0x470B21);
//    ReplaceImage(0x470B3C);
//    ReplaceImage(0x4727E7);
//    ReplaceImage(0x472B42);
//    ReplaceImage(0x4B54A1);
//    RunTime::ResetMemoryContentAt(0x4B549C, sizeof(BuildingDatas));
//    ReplaceImage(0x4B6069);
//    ReplaceImage(0x4B67AF);
//    ReplaceImage(0x4B6C1C);
//
//    ReplaceWidth(0x470974);
//    ReplaceWidth(0x4726A6);
//    ReplaceWidth(0x4727DB);
//    ReplaceWidth(0x4A50C9);
//    ReplaceWidth(0x4A5794);
//    ReplaceWidth(0x4A7501);
//    ReplaceWidth(0x4A76AE);
//    ReplaceWidth(0x4A93E7);
//    ReplaceWidth(0x4A9851);
//    ReplaceWidth(0x4B5DD5);
//    ReplaceWidth(0x4B677F);
//    ReplaceWidth(0x4B6BF3);
//
//    ReplaceHeight(0x47097B);
//    ReplaceHeight(0x472699);
//    ReplaceHeight(0x4727E2);
//    ReplaceHeight(0x4A50BC);
//    ReplaceHeight(0x4A57BE);
//    ReplaceHeight(0x4A74F4);
//    ReplaceHeight(0x4A76C9);
//    ReplaceHeight(0x4A93D6);
//    ReplaceHeight(0x4A9871);
//    ReplaceHeight(0x4B5DDC);
//    ReplaceHeight(0x4B6786);
//    ReplaceHeight(0x4B6BFA);
//
//    ReplaceTemperateFlag(0x4B5DE8);
//    ReplaceTemperateFlag(0x4B5F25);
//    ReplaceTemperateFlag(0x4B6052);
//    ReplaceTemperateFlag(0x4B6792);
//    ReplaceTemperateFlag(0x5213F5);
//
//    ReplaceSnowFlag(0x4B5DE2);
//    ReplaceSnowFlag(0x4B5FB0);
//    ReplaceSnowFlag(0x4B604C);
//    ReplaceSnowFlag(0x4B678C);
//    ReplaceSnowFlag(0x521425);
//
//    ReplaceUrbanFlag(0x4B5DEE);
//    ReplaceUrbanFlag(0x4B603B);
//    ReplaceUrbanFlag(0x4B6058);
//    ReplaceUrbanFlag(0x4B6798);
//    ReplaceUrbanFlag(0x521455);
//
//    ReplaceFacingCount(0x4B605E);
//    ReplaceFacingCount(0x4B6C0A);
//
//    return 0;
//}