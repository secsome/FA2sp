#include <Helpers/Macro.h>

#include "../RunTime.h"

// FinalAlert 2 used a MapPreview buffer in CMapData::InitMinimap(0x4C3D40):
// memset(this->MapPreview, 0xFFu, previewHeight * stride);
// If we create a big map, it will probably corrupt all members following it, like all the INI datas
// 
// However, the buffer sizes only 0x40000
// As it is a bitmap and as how FA2 paint the minimap, the size a map takes is (2 * W * H + 3) / 4 * 3 bytes.
// 256 * 256 * 2 * 3 = 0x60000
// This is the preview buffer size we need instead of stupid FA2's 0x40000,
// which limited the map size to 209 * 209 at max
// (2 * 209 * 209 + 3) / 4 * 3 = 65523 (0xFFF3)
//
// Therefore we just need to replace this buffer and it will works fine

static char MapPreviewBuffer[0x60000];

#define DEFINE_REG_HELPER(to, from) \
void __declspec(naked) to##_##from() \
{ __asm {lea to, [MapPreviewBuffer + from]} }

#define DEFINE_ZERO_HELPER(to) \
void __declspec(naked) to##_##0() \
{ __asm {lea to, [MapPreviewBuffer]} }

namespace PreviewFixDetails
{
    // These two naked function both takes 6 bytes
    // So we can easily copy the op codes from them

    // original op code
    // XX XX (XX) 48 02 08 00

    DEFINE_ZERO_HELPER(esi);
    DEFINE_ZERO_HELPER(edi);
    DEFINE_ZERO_HELPER(edx);
    DEFINE_ZERO_HELPER(eax);
    DEFINE_REG_HELPER(esi, eax);
    DEFINE_REG_HELPER(ecx, eax);
    DEFINE_REG_HELPER(edx, eax);
    DEFINE_REG_HELPER(ebp, eax);
    DEFINE_REG_HELPER(eax, eax);
    DEFINE_REG_HELPER(ebx, eax);
    DEFINE_REG_HELPER(edi, eax);

    static constexpr byte NOP = 0x90;

    inline void DoZero(unsigned long addr, void* fn)
    {
        RunTime::ResetMemoryContentAt(addr - 2, fn, 6);
    }

    inline void DoReg(unsigned long addr, void* fn)
    {
        RunTime::ResetMemoryContentAt(addr - 3, fn, 6);
        RunTime::ResetMemoryContentAt(addr - 3 + 6, &NOP, 1);
    }
}

#undef DEFINE_ZERO_HELPER
#undef DEFINE_REG_HELPER

DEFINE_HOOK(537129, ExeRun_PreviewFix, 9)
{
    using namespace PreviewFixDetails;

    DoZero(0x4168B1, eax_0);
    DoZero(0x45DCC6, eax_0);
    DoZero(0x45E3C5, eax_0);
    DoZero(0x4A23C0, eax_0);
    DoZero(0x4A335F, eax_0);
    DoZero(0x4A44C2, eax_0);
    DoZero(0x4A512B, eax_0);
    DoZero(0x4A6290, eax_0);
    DoZero(0x4A6A13, eax_0);
    DoZero(0x4A7FC5, eax_0);
    DoZero(0x4A8B7A, eax_0);
    DoZero(0x4A940B, eax_0);
    DoZero(0x4A9C8A, eax_0);
    DoZero(0x4B4BB2, eax_0);
    DoZero(0x4C3DC7, edi_0);
    DoZero(0x4C3DF6, eax_0);
    DoZero(0x4C7843, eax_0);

    DoReg(0x4169A9, edi_eax);
    DoReg(0x4169B6, ebx_eax);
    DoReg(0x45DDC1, ebp_eax);
    DoReg(0x45DDCE, ebx_eax);
    DoReg(0x45E4BE, ebp_eax);
    DoReg(0x45E4CB, ecx_eax);
    DoReg(0x4A24C0, ebp_eax);
    DoReg(0x4A24CD, eax_eax);
    DoReg(0x4A346A, ebp_eax);
    DoReg(0x4A3477, edi_eax);
    DoReg(0x4A45B5, ebp_eax);
    DoReg(0x4A45C2, eax_eax);
    DoReg(0x4A521E, ebp_eax);
    DoReg(0x4A522B, eax_eax);
    DoReg(0x4A6383, ebp_eax);
    DoReg(0x4A6390, eax_eax);
    DoReg(0x4A6B0A, ebp_eax);
    DoReg(0x4A6B17, eax_eax);
    DoReg(0x4A80B8, ebp_eax);
    DoReg(0x4A80C5, ebx_eax);
    DoReg(0x4A8C6F, ebp_eax);
    DoReg(0x4A8C7C, ebx_eax);
    DoReg(0x4A94FB, edi_eax);
    DoReg(0x4A9508, ebp_eax);
    DoReg(0x4A9D7F, ebp_eax);
    DoReg(0x4A9D8C, ebx_eax);
    DoReg(0x4B4CAD, ebx_eax);
    DoReg(0x4B4CBA, eax_eax);
    DoReg(0x4BD3C9, esi_eax);
    DoReg(0x4BD3DB, edi_eax);
    DoReg(0x4BDACF, esi_eax);
    DoReg(0x4BDAE1, edi_eax);
    DoReg(0x4BE61D, esi_eax);
    DoReg(0x4BE62F, ebp_eax);
    DoReg(0x4BED9F, esi_eax);
    DoReg(0x4BEDB1, ebp_eax);
    DoReg(0x4BFF91, esi_eax);
    DoReg(0x4BFFA3, edi_eax);
    DoReg(0x4C100E, esi_eax);
    DoReg(0x4C1020, edi_eax);
    DoReg(0x4C793E, esi_eax);
    DoReg(0x4C7952, edi_eax);

    DoZero(0x4BD2AF, esi_0);
    DoZero(0x4BD9B5, esi_0);
    DoZero(0x4BE501, edi_0);
    DoZero(0x4BEC85, edi_0);
    DoZero(0x4BFE59, esi_0);
    DoZero(0x4C0EF4, esi_0);

    return 0;
}