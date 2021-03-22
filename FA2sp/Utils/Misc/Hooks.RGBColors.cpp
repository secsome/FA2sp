#include <MFC/ppmfc_cstring.h>
#include <GlobalVars.h>

#include <algorithm>

// from http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb
struct RgbColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct HsvColor
{
	unsigned char h;
	unsigned char s;
	unsigned char v;
};

constexpr RgbColor HsvToRgb(HsvColor const hsv) noexcept {
	if (hsv.s == 0u) {
		return { hsv.v, hsv.v, hsv.v };
	}

	unsigned char region = hsv.h / 43;
	unsigned char remainder = (hsv.h - (region * 43)) * 6;

	unsigned char p = (hsv.v * (255 - hsv.s)) >> 8;
	unsigned char q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
	unsigned char t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

	switch (region) {
	case 0:
		return { hsv.v, t, p };
	case 1:
		return { q, hsv.v, p };
	case 2:
		return { p, hsv.v, t };
	case 3:
		return { p, q, hsv.v };
	case 4:
		return { t, p, hsv.v };
	default:
		return { hsv.v, p, q };
	}
}

constexpr HsvColor RgbToHsv(RgbColor const rgb) noexcept {
	auto const rgbMin = std::min({ rgb.r, rgb.g, rgb.b });
	auto const rgbMax = std::max({ rgb.r, rgb.g, rgb.b });

	if (rgbMax == 0) {
		return { 0, 0, 0 };
	}

	unsigned char s = 255 * long(rgbMax - rgbMin) / rgbMax;

	if (s == 0) {
		return { 0, s, rgbMax };
	}

	HsvColor hsv{ 0, s, rgbMax };
	if (rgbMax == rgb.r) {
		hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
	}
	else if (rgbMax == rgb.g) {
		hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
	}
	else {
		hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);
	}

	return hsv;
}

// color section support for objects on the map.
// FA2 only supports a set of hardcoded colors that are
// resolved to hardcoded RGB values. this uses the real
// HSV values from the rules file and converts it to RGB.
DEFINE_HOOK(468B44, sub_468760_RGBColor, 5)
{
	//GET_STACK(char const*, pColor, 0xAC);
	REF_STACK(ppmfc::CString, name, STACK_OFFS(0xA4, 0x94));

	auto& rules = GlobalVars::INIFiles::Rules();

	if (strlen(name) > 0) {
		if (auto const pValue = rules.GetString("Colors", name, "0,0,0"))
		{
			// parse 3 unsigned bytes
			HsvColor hsv{};
			if (sscanf_s(pValue, "%hhu,%hhu,%hhu", &hsv.h, &hsv.s, &hsv.v) == 3)
			{
				auto const rgb = HsvToRgb(hsv);

				// clean up
				name.~CString();

				// return this color
				R->EAX<unsigned int>(rgb.r | rgb.g << 8u | rgb.b << 16u);
				return 0x468ED3;
			}
		}
	}
	return 0;
}