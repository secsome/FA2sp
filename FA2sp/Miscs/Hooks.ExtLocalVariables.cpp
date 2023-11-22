#include <Helpers/Macro.h>

#include "../FA2sp.h"

DEFINE_HOOK(4483B1, CLocalVariables_UpdateDialog_ExtVariables, 9)
{
    if (ExtConfigs::ExtVariables || R->EBP() < 100)
        return 0x448148;
    else
        return 0x4483C1;
}