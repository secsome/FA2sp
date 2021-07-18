#include <Helpers/Macro.h>
#include <CINI.h>
#include <GlobalVars.h>

#include <MFC/ppmfc_include.h>

#include <map>

class RGBClass
{
public:
	unsigned char R, G, B;

	operator int()
	{
		return RGB(R, G, B);
	}
};

class HSVClass
{
public:
	unsigned char H, S, V;

	operator RGBClass() const
	{
		if (S == 0u)
			return { V, V, V };

		unsigned char region = H / 43;
		unsigned char remainder = (H - (region * 43)) * 6;

		unsigned char p = (V * (255 - S)) >> 8;
		unsigned char q = (V * (255 - ((S * remainder) >> 8))) >> 8;
		unsigned char t = (V * (255 - ((S * (255 - remainder)) >> 8))) >> 8;

		switch (region) {
		case 0:
			return { V, t, p };
		case 1:
			return { q, V, p };
		case 2:
			return { p, V, t };
		case 3:
			return { p, q, V };
		case 4:
			return { t, p, V };
		default:
			return { V, p, q };
		}
	}
};

DEFINE_HOOK(468760, Miscs_GetColor, 7)
{
	GET_STACK(const char*, pHouse, 0x4);
	GET_STACK(const char*, pColor, 0x8);

	ppmfc::CString color = "";
	if (pHouse)
		if (auto pStr = GlobalVars::INIFiles::CurrentDocument->TryGetString(pHouse, "Color"))
			color = *pStr;

	if (pColor)
		color = pColor;

	HSVClass hsv{ 0,0,0 };
	if (!color.IsEmpty())
	{
		auto const ppValue = GlobalVars::INIFiles::Rules->TryGetString("Colors", color);
		if (ppValue)
			sscanf_s(*ppValue, "%hhu,%hhu,%hhu", &hsv.H, &hsv.S, &hsv.V);
	}

	RGBClass rgb = hsv;
	R->EAX<int>(rgb);

	return 0x468EEB;
	
}