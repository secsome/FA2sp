#include <Helpers/Macro.h>

DEFINE_HOOK(468B44, sub_468760_RGBColor, 5)
{
    // REF_STACK(CString, name, STACK_OFFS(0xA4, 0x94));

    // I love blue
    R->EAX<unsigned int>(0 | 255 << 8 | 0 << 16);

    // return 0;
    return 0x468ED3;
}