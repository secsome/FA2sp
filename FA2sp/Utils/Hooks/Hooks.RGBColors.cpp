#include <Helpers/Macro.h>
#include <CINI.h>
#include <GlobalVars.h>

#include <Drawing.h>
#include <MFC/ppmfc_include.h>

#include <map>

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