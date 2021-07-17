#include <Helpers/Macro.h>
#include <Drawing.h>
#include <Palette.h>

#include "../../FA2sp.h"

#define INVALID_COLOR_VALUE 0xFFFFFFFFu
#define GLOBAL_REMAP_START 16
#define GLOBAL_REMAP_END 31

// [16, 31]
//struct RemapColors
//{
//    ColorStruct Data[16];
//
//    /// <param name="index">From 16 to 31</param>
//	ColorStruct GetColorFromPalIndex(int index) { return Data[index - 16]; }
//};

class RemapColorHelper
{
public:
	static BGRStruct GetRemapColor(Palette* pal, BGRStruct RemapColor, short i)
	{
		BGRStruct ret;
		
		ret.R = pal->Data[i].R / RemapColor.R * 255;
		ret.G = pal->Data[i].G / RemapColor.G * 255;
		ret.B = pal->Data[i].B / RemapColor.B * 255;

		return ret;
	}

  //  static RemapColors GetRemapColor(Palette& pal, COLORREF dwBaseColor)
  //  {
		//RemapColors ret;

		//if (dwBaseColor == INVALID_COLOR_VALUE)
		//	return ret;

		//ColorStruct RemapColor;

		//RemapColor.red = dwBaseColor & 0x000000FF;
		//RemapColor.green = (dwBaseColor & 0x0000FF00) >> 8;
		//RemapColor.blue = (dwBaseColor & 0x00FF0000) >> 16;

		//for (int i = 0; i <= 15; ++i)
		//{
		//	BYTE R, G, B;
		//	R = RemapColor.red * (16 - i) / 16;
		//	G = RemapColor.green * (16 - i) / 16;
		//	B = RemapColor.blue * (16 - i) / 16;
		//	ret.Data[i] = { R,G,B };
		//}

		//return ret;
  //  }
};

DEFINE_HOOK(474126, CIsoView_Draw_RemapColor_Infantry, 6)
{
	GET_STACK(BGRStruct*, pColor, STACK_OFFS(0xD18, 0xD04));
	REF_STACK(DrawDataStruct, data, STACK_OFFS(0xD18, 0x9B0));
	GET(int, index, EAX);
	unsigned char i = LOBYTE(index);
	GET(int, tester, ECX);

	auto remapped = RemapColorHelper::GetRemapColor(data.pPalette, *pColor, i);

	Logger::Raw("\nECX = %d\n", tester);
	Logger::Raw("Color before remapped = %d %d %d\n", pColor->R, pColor->G, pColor->B);
	Logger::Raw("Color after remapped = %d %d %d\n", remapped.R, remapped.G, remapped.B);
	Logger::Raw("Index = %d, palcolor = %d %d %d\n\n", i, data.pPalette->Data[i].R, data.pPalette->Data[i].G, data.pPalette->Data[i].B);

	pColor->R = remapped.R;
	pColor->G = remapped.G;
	pColor->B = remapped.B;

	return 0;
}