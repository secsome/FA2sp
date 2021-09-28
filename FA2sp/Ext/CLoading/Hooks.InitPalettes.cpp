#include "Body.h"

#include <CPalette.h>
#include <FAMemory.h>

DEFINE_HOOK(48B020, CLoading_InitPalettes, 7)
{
    GET(CLoadingExt*, pThis, ECX);

    BytePalette::LoadedPaletteCount() = 0;

    auto loadPalette = [&pThis](const char* pName, int& to) -> bool
    {
        if (BytePalette::LoadedPaletteCount() > 0xFF)
            return false;

        if (auto pBuffer = (BytePalette*)pThis->ReadWholeFile(pName))
        {
            for (int i = 0; i < 256; ++i)
            {
                pBuffer->Data[i].red <<= 2;
                pBuffer->Data[i].green <<= 2;
                pBuffer->Data[i].blue <<= 2;
            }
            to = ++BytePalette::LoadedPaletteCount();
            BytePalette::LoadedPalettes[BytePalette::LoadedPaletteCount()] = *pBuffer;
            BytePalette::LoadedPaletteFlag[BytePalette::LoadedPaletteCount()] = TRUE;
            GameDelete(pBuffer);
            return true;
        }

        return false;
    };

    loadPalette("isotem.pal", pThis->PAL_ISOTEM);
    loadPalette("isosno.pal", pThis->PAL_ISOSNO);
    loadPalette("isourb.pal", pThis->PAL_ISOURB);
    loadPalette("isoubn.pal", pThis->PAL_ISOUBN);
    loadPalette("isolun.pal", pThis->PAL_ISOLUN);
    loadPalette("isodes.pal", pThis->PAL_ISODES);

    loadPalette("unittem.pal", pThis->PAL_UNITTEM);
    loadPalette("unitsno.pal", pThis->PAL_UNITSNO);
    loadPalette("uniturb.pal", pThis->PAL_UNITURB);
    loadPalette("unitubn.pal", pThis->PAL_UNITUBN);
    loadPalette("unitlun.pal", pThis->PAL_UNITLUN);
    loadPalette("unitdes.pal", pThis->PAL_UNITDES);

    loadPalette("temperat.pal", pThis->PAL_TEMPERAT);
    loadPalette("snow.pal", pThis->PAL_SNOW);
    loadPalette("urban.pal", pThis->PAL_URBAN);
    loadPalette("urbann.pal", pThis->PAL_URBANN);
    loadPalette("lunar.pal", pThis->PAL_LUNAR);
    loadPalette("desert.pal", pThis->PAL_DESERT);

    if (!loadPalette("libtem.pal", pThis->PAL_LIB_ID2124019542))
        loadPalette("_ID2124019542", pThis->PAL_LIB_ID2124019542);

    return 0x48C3CD;
}