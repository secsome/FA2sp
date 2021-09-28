#include "Palettes.h"

#include <CPalette.h>
#include <Drawing.h>
#include <CMixFile.h>
#include <CLoading.h>

std::map<ppmfc::CString, Palette*> Palettes::LoadedPalettes;
std::map<Palette*, std::map<BGRStruct, Palette>> Palettes::RemappedPalettes;

void Palettes::Init()
{
    LoadedPalettes["isotem.pal"] = Palette::PALETTE_ISO;
    LoadedPalettes["isosno.pal"] = Palette::PALETTE_ISO;
    LoadedPalettes["isourb.pal"] = Palette::PALETTE_ISO;
    LoadedPalettes["isoubn.pal"] = Palette::PALETTE_ISO;
    LoadedPalettes["isolun.pal"] = Palette::PALETTE_ISO;
    LoadedPalettes["isodes.pal"] = Palette::PALETTE_ISO;
    
    LoadedPalettes["unittem.pal"] = Palette::PALETTE_UNIT;
    LoadedPalettes["unitsno.pal"] = Palette::PALETTE_UNIT;
    LoadedPalettes["uniturb.pal"] = Palette::PALETTE_UNIT;
    LoadedPalettes["unitubn.pal"] = Palette::PALETTE_UNIT;
    LoadedPalettes["unitlun.pal"] = Palette::PALETTE_UNIT;
    LoadedPalettes["unitdes.pal"] = Palette::PALETTE_UNIT;

    LoadedPalettes["temperat.pal"] = Palette::PALETTE_THEATER;
    LoadedPalettes["snow.pal"] = Palette::PALETTE_THEATER;
    LoadedPalettes["urban.pal"] = Palette::PALETTE_THEATER;
    LoadedPalettes["urbann.pal"] = Palette::PALETTE_THEATER;
    LoadedPalettes["lunar.pal"] = Palette::PALETTE_THEATER;
    LoadedPalettes["desert.pal"] = Palette::PALETTE_THEATER;

    LoadedPalettes["libtem.pal"] = Palette::PALETTE_LIB;
}

Palette* Palettes::LoadPalette(ppmfc::CString palName)
{
    if (LoadedPalettes.size() == 0)
        Palettes::Init();

    auto itr = LoadedPalettes.find(palName);
    if (itr != LoadedPalettes.end())
        return itr->second;

    if (BytePalette* pBuffer = (BytePalette*)CLoading::Instance->ReadWholeFile(palName))
    {
        auto pPal = GameCreate<Palette>();
        for (int i = 0; i < 256; ++i)
        {
            pPal->Data[i].R = (*pBuffer)[i].red << 2;
            pPal->Data[i].G = (*pBuffer)[i].green << 2;
            pPal->Data[i].B = (*pBuffer)[i].blue << 2;
        }
        GameDelete(pBuffer);
        LoadedPalettes[palName] = pPal;
        return pPal;
    }

    return nullptr;
}

Palette* Palettes::GetRemap(ppmfc::CString palName, BGRStruct color)
{
    if (LoadedPalettes.find(palName) == LoadedPalettes.end())
        if (!LoadPalette(palName))
            return nullptr;

    return GetRemap(LoadedPalettes[palName], color);
}

Palette* Palettes::GetRemap(Palette* pal, BGRStruct color)
{
    auto itr = RemappedPalettes.find(pal);
    if (itr != RemappedPalettes.end())
    {
        auto itr2 = itr->second.find(color);
        if (itr2 != itr->second.end())
            return &itr2->second;
    }

    // Not found, create remap color
    auto& buffer = RemappedPalettes[pal][color];
    memcpy_s(&buffer, sizeof(Palette), pal, sizeof(Palette));
    for (int i = 16; i <= 31; ++i)
    {
        int ii = i - 16;
        double cosval = ii * 0.08144869842640204 + 0.3490658503988659;
        double sinval = ii * 0.04654211338651545 + 0.8726646259971648;
        if (!ii)
            cosval = 0.1963495408493621;

        RGBClass rgb_remap{ color.R,color.G,color.B };
        HSVClass hsv_remap = rgb_remap;
        hsv_remap.H = hsv_remap.H;
        hsv_remap.S = (unsigned char)(std::sin(sinval) * hsv_remap.S);
        hsv_remap.V = (unsigned char)(std::cos(cosval) * hsv_remap.V);
        RGBClass result = hsv_remap;

        buffer[i] = { result.B,result.G,result.R };
    }
    return &buffer;
}

void Palettes::Clear()
{
    for (auto& pair : LoadedPalettes)
        if (pair.second != Palette::PALETTE_UNIT &&
            pair.second != Palette::PALETTE_ISO &&
            pair.second != Palette::PALETTE_THEATER &&
            pair.second != Palette::PALETTE_LIB)
            GameDelete(pair.second);

    LoadedPalettes.clear();
    RemappedPalettes.clear();
    Init();
}
