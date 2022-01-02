#include <Helpers/Macro.h>

#include "../RunTime.h"

// 256 * 256 * 2 * 3 = 0x60000
// This is the preview buffer size we need instead of stupid FA2's 0x40000,
// which limited the map size to 209*209 at max
static char MapPreviewBuffer[0x60000];

#define DEFINE_REG_HELPER(to, from) \
void __declspec(naked) to##_##from() \
{ __asm {lea to, [MapPreviewBuffer + from]} }

#define DEFINE_ZERO_HELPER(to) \
void __declspec(naked) to##_##0() \
{ __asm {lea to, [MapPreviewBuffer]} }

namespace PreviewFixDetails
{
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

    char nop = 0x90;

    void DoZero(unsigned long addr, void* fn)
    {
        RunTime::ResetMemoryContentAt(addr, fn, 6);
    }

    void DoReg(unsigned long addr, void* fn)
    {
        RunTime::ResetMemoryContentAt(addr, fn, 6);
        RunTime::ResetMemoryContentAt(addr + 6, &nop, 1);
    }
}

#undef DEFINE_ZERO_HELPER
#undef DEFINE_REG_HELPER

DEFINE_HOOK(537129, ExeRun_PreviewFix, 9)
{
    using namespace PreviewFixDetails;

    DoZero(0x4168B1 - 2, eax_0);
    DoZero(0x45DCC6 - 2, eax_0);
    DoZero(0x45E3C5 - 2, eax_0);
    DoZero(0x4A23C0 - 2, eax_0);
    DoZero(0x4A335F - 2, eax_0);
    DoZero(0x4A44C2 - 2, eax_0);
    DoZero(0x4A512B - 2, eax_0);
    DoZero(0x4A6290 - 2, eax_0);
    DoZero(0x4A6A13 - 2, eax_0);
    DoZero(0x4A7FC5 - 2, eax_0);
    DoZero(0x4A8B7A - 2, eax_0);
    DoZero(0x4A940B - 2, eax_0);
    DoZero(0x4A9C8A - 2, eax_0);
    DoZero(0x4B4BB2 - 2, eax_0);
    DoZero(0x4C3DC7 - 2, edi_0);
    DoZero(0x4C3DF6 - 2, eax_0);
    DoZero(0x4C7843 - 2, eax_0);

    DoReg(0x4169A9 - 3, edi_eax);
    DoReg(0x4169B6 - 3, ebx_eax);
    DoReg(0x45DDC1 - 3, ebp_eax);
    DoReg(0x45DDCE - 3, ebx_eax);
    DoReg(0x45E4BE - 3, ebp_eax);
    DoReg(0x45E4CB - 3, ecx_eax);
    DoReg(0x4A24C0 - 3, ebp_eax);
    DoReg(0x4A24CD - 3, eax_eax);
    DoReg(0x4A346A - 3, ebp_eax);
    DoReg(0x4A3477 - 3, edi_eax);
    DoReg(0x4A45B5 - 3, ebp_eax);
    DoReg(0x4A45C2 - 3, eax_eax);
    DoReg(0x4A521E - 3, ebp_eax);
    DoReg(0x4A522B - 3, eax_eax);
    DoReg(0x4A6383 - 3, ebp_eax);
    DoReg(0x4A6390 - 3, eax_eax);
    DoReg(0x4A6B0A - 3, ebp_eax);
    DoReg(0x4A6B17 - 3, eax_eax);
    DoReg(0x4A80B8 - 3, ebp_eax);
    DoReg(0x4A80C5 - 3, ebx_eax);
    DoReg(0x4A8C6F - 3, ebp_eax);
    DoReg(0x4A8C7C - 3, ebx_eax);
    DoReg(0x4A94FB - 3, edi_eax);
    DoReg(0x4A9508 - 3, ebp_eax);
    DoReg(0x4A9D7F - 3, ebp_eax);
    DoReg(0x4A9D8C - 3, ebx_eax);
    DoReg(0x4B4CAD - 3, ebx_eax);
    DoReg(0x4B4CBA - 3, eax_eax);
    DoReg(0x4BD3C9 - 3, esi_eax);
    DoReg(0x4BD3DB - 3, edi_eax);
    DoReg(0x4BDACF - 3, esi_eax);
    DoReg(0x4BDAE1 - 3, edi_eax);
    DoReg(0x4BE61D - 3, esi_eax);
    DoReg(0x4BE62F - 3, ebp_eax);
    DoReg(0x4BED9F - 3, esi_eax);
    DoReg(0x4BEDB1 - 3, ebp_eax);
    DoReg(0x4BFF91 - 3, esi_eax);
    DoReg(0x4BFFA3 - 3, edi_eax);
    DoReg(0x4C100E - 3, esi_eax);
    DoReg(0x4C1020 - 3, edi_eax);
    DoReg(0x4C793E - 3, esi_eax);
    DoReg(0x4C7952 - 3, edi_eax);

    DoZero(0x4BD2AF - 2, esi_0);
    DoZero(0x4BD9B5 - 2, esi_0);
    DoZero(0x4BE501 - 2, edi_0);
    DoZero(0x4BEC85 - 2, edi_0);
    DoZero(0x4BFE59 - 2, esi_0);
    DoZero(0x4C0EF4 - 2, esi_0);

    return 0;
}