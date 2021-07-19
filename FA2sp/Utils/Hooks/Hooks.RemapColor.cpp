#include <Helpers/Macro.h>
#include <Drawing.h>
#include <Palette.h>

#include <map>

#define GLOBAL_REMAP_START 16
#define GLOBAL_REMAP_END 31

class RemapColorHelper
{
public:

	static void RemapPalette(Palette* pPal, BGRStruct RemapColor, Palette* pReload = nullptr)
	{
		if (pReload)
			memcpy_s(pPal->Data, sizeof Palette, pReload->Data, sizeof Palette);

		for (int i = GLOBAL_REMAP_START; i <= GLOBAL_REMAP_END; i++)
		{
			int ii = i - 16;
			double cosval = ii * 0.08144869842640204 + 0.3490658503988659;
			double sinval = ii * 0.04654211338651545 + 0.8726646259971648;
			if (!ii)
				cosval = 0.1963495408493621;

			RGBClass rgb_remap{ RemapColor.R,RemapColor.G,RemapColor.B };
			HSVClass hsv_remap = rgb_remap;
			hsv_remap.H = hsv_remap.H;
			hsv_remap.S = (unsigned char)(std::sin(sinval) * hsv_remap.S);
			hsv_remap.V = (unsigned char)(std::cos(cosval) * hsv_remap.V);
			RGBClass result = hsv_remap;

			pPal->Data[i] = { result.B,result.G,result.R };
			// pPal->Data[i].R = RemapColor.R * (GLOBAL_REMAP_END + 1 - i) / (GLOBAL_REMAP_END + 1 - GLOBAL_REMAP_START);
			// pPal->Data[i].G = RemapColor.G * (GLOBAL_REMAP_END + 1 - i) / (GLOBAL_REMAP_END + 1 - GLOBAL_REMAP_START);
			// pPal->Data[i].B = RemapColor.B * (GLOBAL_REMAP_END + 1 - i) / (GLOBAL_REMAP_END + 1 - GLOBAL_REMAP_START);
		}
	}

	static Palette* GetRemappedPalette(BGRStruct RemapColor)
	{
		auto itr = RemappedPalettes.find(RemapColor);
		if (itr != RemappedPalettes.end())
			return &itr->second;
		else
		{
			auto& tmp = RemappedPalettes.insert(std::make_pair(RemapColor, Palette())).first;
			RemapPalette(&tmp->second, RemapColor, Palette::PALETTE_UNIT);
			return &tmp->second;
		}
	}

	static void Clear()
	{
		RemappedPalettes.clear();
	}
private:
	static std::map<BGRStruct, Palette> RemappedPalettes;

};

std::map<BGRStruct, Palette> RemapColorHelper::RemappedPalettes;

DEFINE_HOOK(49D2C0, LoadMap_ClearUp, 5)
{
	RemapColorHelper::Clear();

	return 0;
}

#define REMAP_FIX_PALETTE_SET(hook_addr, hook_name, data_off, color_off) \
DEFINE_HOOK(hook_addr,hook_name,7) \
{ \
REF_STACK(DrawDataStruct, data, STACK_OFFS(0xD18, data_off)); \
GET_STACK(BGRStruct*, pColor, STACK_OFFS(0xD18, color_off)); \
if(data.pPalette == Palette::PALETTE_UNIT) \
	data.pPalette = RemapColorHelper::GetRemappedPalette(*pColor); \
return 0; \
}

#define REMAP_FIX_JMP(hook_addr,hook_name,ret_addr) \
DEFINE_HOOK(hook_addr,hook_name,6) \
{ \
return ret_addr; \
}

#define REMAP_FIX_HOOK(set_addr, hook_name,data_off,color_off, jump_addr,jump_to)\
REMAP_FIX_PALETTE_SET(set_addr,hook_name ## _SetPalette ,0x ## data_off,0x ## color_off); \
REMAP_FIX_JMP(jump_addr,hook_name ## _JumpAway,0x ## jump_to);

REMAP_FIX_HOOK(470D34, CIsoView_Draw_RemapColor_Building, AFC, CF0, 470DC0, 470DEC);
REMAP_FIX_HOOK(471555, CIsoView_Draw_RemapColor_PowerUp1, 96C, CF4, 4715DF, 471604);
REMAP_FIX_HOOK(471CF0, CIsoView_Draw_RemapColor_PowerUp2, 94C, CF4, 471D7A, 471D9F);
REMAP_FIX_HOOK(472444, CIsoView_Draw_RemapColor_PowerUp3, 98C, CF4, 4724CD, 4724F2);
REMAP_FIX_HOOK(472DCD, CIsoView_Draw_RemapColor_Basenode, 9DC, CF4, 472E73, 472E96);
REMAP_FIX_HOOK(47337C, CIsoView_Draw_RemapColor_UnitsSHP, B7C, D04, 4733FC, 47342A);
REMAP_FIX_HOOK(4735CE, CIsoView_Draw_RemapColor_UnitsVXL, B7C, D04, 47364E, 47367C);
REMAP_FIX_HOOK(4739FF, CIsoView_Draw_RemapColor_AircraftsSHP, BE4, D04, 473A7F, 473AAD);
REMAP_FIX_HOOK(473C51, CIsoView_Draw_RemapColor_AircraftsVXL, BE4, D04, 473A7F, 473CFF);
REMAP_FIX_HOOK(474087, CIsoView_Draw_RemapColor_Infantry, 9B0, D04, 474109, 474135);

#undef REMAP_FIX_PALETTE_SET
#undef REMAP_FIX_JMP
#undef REMAP_FIX_HOOK