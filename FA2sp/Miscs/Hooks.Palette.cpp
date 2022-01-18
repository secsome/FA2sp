#include <Helpers/Macro.h>
#include <Drawing.h>
#include <CPalette.h>
#include <CLoading.h>

#include "Palettes.h"

DEFINE_HOOK(4B9F7A, CreateMap_ClearUp, 5)
{
	PalettesManager::Release();

	return 0;
}

DEFINE_HOOK(49D2C0, LoadMap_ClearUp, 5)
{
	PalettesManager::Release();

	return 0;
}

#define REMAP_FIX_PALETTE_SET(hook_addr, hook_name, data_off, color_off) \
DEFINE_HOOK(hook_addr,hook_name,7) \
{ \
	REF_STACK(ImageDataClass, data, STACK_OFFS(0xD18, data_off)); \
	GET_STACK(BGRStruct*, pColor, STACK_OFFS(0xD18, color_off)); \
	data.pPalette = PalettesManager::GetPalette(data.pPalette, *pColor); \
	return 0; \
}

#define REMAP_FIX_JMP(hook_addr,hook_name,ret_addr) \
DEFINE_HOOK(hook_addr,hook_name,6) \
{ \
	return ret_addr; \
}

#define REMAP_FIX_HOOK(set_addr, hook_name, data_off, color_off, jump_addr, jump_to)\
REMAP_FIX_PALETTE_SET(set_addr,hook_name ## _SetPalette ,0x ## data_off,0x ## color_off); \
REMAP_FIX_JMP(jump_addr,hook_name ## _JumpAway,0x ## jump_to);

REMAP_FIX_HOOK(470D34, CIsoView_Draw_Palette_Building, AFC, CF0, 470DC0, 470DEC);
REMAP_FIX_HOOK(471555, CIsoView_Draw_Palette_PowerUp1, 96C, CF4, 4715DF, 471604);
REMAP_FIX_HOOK(471CF0, CIsoView_Draw_Palette_PowerUp2, 94C, CF4, 471D7A, 471D9F);
REMAP_FIX_HOOK(472444, CIsoView_Draw_Palette_PowerUp3, 98C, CF4, 4724CD, 4724F2);
REMAP_FIX_HOOK(472DCD, CIsoView_Draw_Palette_Basenode, 9DC, CF4, 472E73, 472E96);
REMAP_FIX_HOOK(47337C, CIsoView_Draw_Palette_UnitsSHP, B7C, D04, 4733FC, 47342A);
REMAP_FIX_HOOK(4735CE, CIsoView_Draw_Palette_UnitsVXL, B7C, D04, 47364E, 47367C);
REMAP_FIX_HOOK(4739FF, CIsoView_Draw_Palette_AircraftsSHP, BE4, D04, 473A7F, 473AAD);
REMAP_FIX_HOOK(473C51, CIsoView_Draw_Palette_AircraftsVXL, BE4, D04, 473A7F, 473CFF);
REMAP_FIX_HOOK(474087, CIsoView_Draw_Palette_Infantry, 9B0, D04, 474109, 474135);

#undef REMAP_FIX_PALETTE_SET
#undef REMAP_FIX_JMP
#undef REMAP_FIX_HOOK

DEFINE_HOOK(48C3F6, CIsoView_InitTMPs_SkipReset, 5)
{
	if (!PalettesManager::ManualReloadTMP)
		CLoading::Instance->InitTMPs_Reset();
	return 0x48C3FB;
}

DEFINE_HOOK(46DEF7, CIsoView_Draw_Palette_Iso_Set, 5)
{
	PalettesManager::CacheAndTintCurrentIso();

	return 0;
}

DEFINE_HOOK(474AE3, CIsoView_Draw_Palette_Iso_Revert, 6)
{
	PalettesManager::RestoreCurrentIso();

	return 0;
}