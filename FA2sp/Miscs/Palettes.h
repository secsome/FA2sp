#pragma once

#include "../FA2sp.h"

#include <CPalette.h>

#include <map>

// References from ccmaps-net
// In fact the lighting should just be integers (from YR)
// R = Lighting.R * 100.0 + 0.1
// G = Lighting.G * 100.0 + 0.1
// B = Lighting.B * 100.0 + 0.1
// Ambient = Lighting.Ambient * 100.0 + 0.1
// Ground = Lighting.Ground * 1000.0 + 0.1
// Level = Lighting.Level * 1000.0 + 0.1
// I just choose to take a reference from ccmaps-net code - secsome

struct LightingStruct
{
    float Red;
    float Green;
    float Blue;
    float Ground;
    float Ambient;
    float Level;

    bool operator==(const LightingStruct& another) const
    {
        return
            Red == another.Red &&
            Green == another.Green &&
            Blue == another.Blue &&
            Ground == another.Ground &&
            Ambient == another.Ambient &&
            Level == another.Level;
    }
    bool operator!=(const LightingStruct& another) const
    {
        return !(*this == another);
    }
    bool operator<(const LightingStruct& another) const
    {
        return
            std::tie(Red, Green, Blue, Ground, Ambient, Level) <
            std::tie(another.Red, another.Green, another.Blue, another.Ground, another.Ambient, another.Level);
    }

    static LightingStruct GetCurrentLighting();

    static const LightingStruct NoLighting;
};

class LightingPalette
{
private:
    Palette* OriginPalette;
    float RedMult;
    float GreenMult;
    float BlueMult;
    float AmbientMult;
    Palette Colors;

public:
    LightingPalette(Palette& originPal);
    void AdjustLighting(LightingStruct& lighting, int level = 0, bool tint = true);
    void ResetColors();
    void RemapColors(BGRStruct color);
    void TintColors(bool isObject = false);
    Palette* GetPalette();
};

class PalettesManager
{
    static std::map<ppmfc::CString, Palette*> OriginPaletteFiles;
    static std::map<Palette*, std::map<std::pair<BGRStruct, LightingStruct>, LightingPalette>> CalculatedPaletteFiles;
    static Palette* CurrentIso;

public:

    static void Init();
    static void Release();

    static void CacheCurrentIso();
    static void RestoreCurrentIso();

    static bool ManualReloadTMP;

    static Palette* GetCurrentIso();
    static void CacheAndTintCurrentIso();
    static Palette* LoadPalette(ppmfc::CString palname);
    static Palette* GetPalette(Palette* pPal, BGRStruct& color, bool remap = true);
};