#include "Palettes.h"

#include <CPalette.h>
#include <Drawing.h>
#include <CMixFile.h>
#include <CLoading.h>

#include <algorithm>

#include "../Ext/CFinalSunDlg/Body.h"

const LightingStruct LightingStruct::NoLighting = { -1,-1,-1,-1,-1,-1 };

std::map<ppmfc::CString, Palette*> PalettesManager::OriginPaletteFiles;
std::map<Palette*, std::map<std::pair<BGRStruct, LightingStruct>, LightingPalette>> PalettesManager::CalculatedPaletteFiles;
Palette* PalettesManager::CurrentIso;
bool PalettesManager::ManualReloadTMP = false;

void PalettesManager::Init()
{
    PalettesManager::OriginPaletteFiles["isotem.pal"] = Palette::PALETTE_ISO;
    PalettesManager::OriginPaletteFiles["isosno.pal"] = Palette::PALETTE_ISO;
    PalettesManager::OriginPaletteFiles["isourb.pal"] = Palette::PALETTE_ISO;
    PalettesManager::OriginPaletteFiles["isoubn.pal"] = Palette::PALETTE_ISO;
    PalettesManager::OriginPaletteFiles["isolun.pal"] = Palette::PALETTE_ISO;
    PalettesManager::OriginPaletteFiles["isodes.pal"] = Palette::PALETTE_ISO;
    
    PalettesManager::OriginPaletteFiles["unittem.pal"] = Palette::PALETTE_UNIT;
    PalettesManager::OriginPaletteFiles["unitsno.pal"] = Palette::PALETTE_UNIT;
    PalettesManager::OriginPaletteFiles["uniturb.pal"] = Palette::PALETTE_UNIT;
    PalettesManager::OriginPaletteFiles["unitubn.pal"] = Palette::PALETTE_UNIT;
    PalettesManager::OriginPaletteFiles["unitlun.pal"] = Palette::PALETTE_UNIT;
    PalettesManager::OriginPaletteFiles["unitdes.pal"] = Palette::PALETTE_UNIT;

    PalettesManager::OriginPaletteFiles["temperat.pal"] = Palette::PALETTE_THEATER;
    PalettesManager::OriginPaletteFiles["snow.pal"] = Palette::PALETTE_THEATER;
    PalettesManager::OriginPaletteFiles["urban.pal"] = Palette::PALETTE_THEATER;
    PalettesManager::OriginPaletteFiles["urbann.pal"] = Palette::PALETTE_THEATER;
    PalettesManager::OriginPaletteFiles["lunar.pal"] = Palette::PALETTE_THEATER;
    PalettesManager::OriginPaletteFiles["desert.pal"] = Palette::PALETTE_THEATER;

    PalettesManager::OriginPaletteFiles["libtem.pal"] = Palette::PALETTE_LIB;
}

void PalettesManager::Release()
{
    for (auto& pair : PalettesManager::OriginPaletteFiles)
        if (pair.second != Palette::PALETTE_UNIT &&
            pair.second != Palette::PALETTE_ISO &&
            pair.second != Palette::PALETTE_THEATER &&
            pair.second != Palette::PALETTE_LIB)
            GameDelete(pair.second);

    PalettesManager::OriginPaletteFiles.clear();
    PalettesManager::CalculatedPaletteFiles.clear();

    PalettesManager::RestoreCurrentIso();

    Init();
}

void PalettesManager::CacheCurrentIso()
{
    if (!PalettesManager::CurrentIso)
        PalettesManager::CurrentIso = GameCreate<Palette>();

    memcpy(PalettesManager::CurrentIso, Palette::PALETTE_ISO, 768);
}

void PalettesManager::RestoreCurrentIso()
{
    if (PalettesManager::CurrentIso)
    {
        memcpy(Palette::PALETTE_ISO, PalettesManager::CurrentIso, 768);
        GameDelete(PalettesManager::CurrentIso);
        PalettesManager::CurrentIso = nullptr;
    }
}

Palette* PalettesManager::GetCurrentIso()
{
    return PalettesManager::CurrentIso;
}

void PalettesManager::CacheAndTintCurrentIso()
{
    PalettesManager::CacheCurrentIso();
    BGRStruct empty;
    auto pPal = PalettesManager::GetPalette(Palette::PALETTE_ISO, empty, false);
    memcpy(Palette::PALETTE_ISO, pPal, 768);
}

Palette* PalettesManager::LoadPalette(ppmfc::CString palname)
{
    auto itr = PalettesManager::OriginPaletteFiles.find(palname);
    if (itr != PalettesManager::OriginPaletteFiles.end())
        return itr->second;

    if (auto pBuffer = (BytePalette*)CLoading::Instance->ReadWholeFile(palname))
    {
        auto pPalette = GameCreate<Palette>();
        for (int i = 0; i < 256; ++i)
        {
            pPalette->Data[i].R = pBuffer->Data[i].red << 2;
            pPalette->Data[i].G = pBuffer->Data[i].green << 2;
            pPalette->Data[i].B = pBuffer->Data[i].blue << 2;
        }
        GameDelete(pBuffer);
        PalettesManager::OriginPaletteFiles[palname] = pPalette;
        return pPalette;
    }

    return nullptr;
}

Palette* PalettesManager::GetPalette(Palette* pPal, BGRStruct& color, bool remap)
{
    LightingStruct lighting = LightingStruct::GetCurrentLighting();

    auto itr = PalettesManager::CalculatedPaletteFiles[pPal].find(std::make_pair(color, lighting));
    if (itr != PalettesManager::CalculatedPaletteFiles[pPal].end())
        return itr->second.GetPalette();

    auto& p = PalettesManager::CalculatedPaletteFiles[pPal].emplace(
        std::make_pair(std::make_pair(color, lighting), LightingPalette(*pPal))
    ).first->second;

    if (remap)
        p.RemapColors(color);
    else
        p.ResetColors();

    if (lighting != LightingStruct::NoLighting)
    {
        p.AdjustLighting(lighting);
        p.TintColors();
    }
    return p.GetPalette();
}

LightingStruct LightingStruct::GetCurrentLighting()
{
    LightingStruct ret;
    switch (CFinalSunDlgExt::CurrentLighting)
    {
    case 31001:
        ret.Red = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Red", 1.0));
        ret.Green = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Green", 1.0));
        ret.Blue = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Blue", 0.5));
        ret.Ambient = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Ambient", 1.0));
        ret.Ground = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Ground", 0.008));
        ret.Level = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "Level", 0.087));
        return ret;
    case 31002:
        ret.Red = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonRed", 1.0));
        ret.Green = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonGreen", 1.0));
        ret.Blue = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonBlue", 0.5));
        ret.Ambient = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonAmbient", 1.0));
        ret.Ground = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonGround", 0.008));
        ret.Level = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "IonLevel", 0.087));
        return ret;
    case 31003:
        ret.Red = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorRed", 1.0));
        ret.Green = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorGreen", 1.0));
        ret.Blue = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorBlue", 0.5));
        ret.Ambient = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorAmbient", 1.0));
        ret.Ground = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorGround", 0.008));
        ret.Level = static_cast<float>(CINI::CurrentDocument->GetDouble("Lighting", "DominatorLevel", 0.087));
        return ret;
    }

    // 31000
    return LightingStruct::NoLighting;
}

LightingPalette::LightingPalette(Palette& originPal)
{
    this->OriginPalette = &originPal;
    this->ResetColors();
}

void LightingPalette::AdjustLighting(LightingStruct& lighting, int level, bool tint)
{
    this->AmbientMult = lighting.Ambient - lighting.Ground + lighting.Level * level;
    if (tint)
    {
        this->RedMult = lighting.Red;
        this->GreenMult = lighting.Green;
        this->BlueMult = lighting.Blue;
    }
}

void LightingPalette::ResetColors()
{
    this->Colors = *this->OriginPalette;
}

void LightingPalette::RemapColors(BGRStruct color)
{
    this->ResetColors();
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

        this->Colors[i] = { result.B,result.G,result.R };
    }
}

void LightingPalette::TintColors(bool isObject)
{
    this->RedMult = std::clamp(this->RedMult, 0.0f, 2.0f);
    this->GreenMult = std::clamp(this->GreenMult, 0.0f, 2.0f);
    this->BlueMult = std::clamp(this->BlueMult, 0.0f, 2.0f);
    this->AmbientMult = std::clamp(this->AmbientMult, 0.0f, 2.0f);

    auto rmult = this->AmbientMult * this->RedMult;
    auto gmult = this->AmbientMult * this->GreenMult;
    auto bmult = this->AmbientMult * this->BlueMult;

    for (int i = 0; i < 240; ++i)
    {
        this->Colors[i].R = (unsigned char)std::min(this->Colors[i].R * rmult, 255.0f);
        this->Colors[i].G = (unsigned char)std::min(this->Colors[i].G * gmult, 255.0f);
        this->Colors[i].B = (unsigned char)std::min(this->Colors[i].B * bmult, 255.0f);
    }
    if (!isObject)
    {
        for (int i = 240; i < 255; ++i)
        {
            this->Colors[i].R = (unsigned char)std::min(this->Colors[i].R * rmult, 255.0f);
            this->Colors[i].G = (unsigned char)std::min(this->Colors[i].G * gmult, 255.0f);
            this->Colors[i].B = (unsigned char)std::min(this->Colors[i].B * bmult, 255.0f);
        }
    }
    this->Colors[255].R = (unsigned char)std::min(this->Colors[255].R * rmult, 255.0f);
    this->Colors[255].G = (unsigned char)std::min(this->Colors[255].G * gmult, 255.0f);
    this->Colors[255].B = (unsigned char)std::min(this->Colors[255].B * bmult, 255.0f);
}

Palette* LightingPalette::GetPalette()
{
    return &this->Colors;
}