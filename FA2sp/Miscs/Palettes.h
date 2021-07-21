#pragma once

#include "../FA2sp.h"

#include <CPalette.h>

#include <map>

class Palettes
{
public:
    static void Init();
    static Palette* LoadPalette(ppmfc::CString palName);
    static Palette* GetRemap(ppmfc::CString palName, BGRStruct color);
    static Palette* GetRemap(Palette* pal, BGRStruct color);
    static void Clear();

private:
    static std::map<ppmfc::CString, Palette*> LoadedPalettes;
    static std::map<Palette*, std::map<BGRStruct, Palette>> RemappedPalettes;
};