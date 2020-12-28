#include "Body.h"

void CTaskForceExt::ProgramStartupInit()
{
    RunTime::ResetMemoryContentAt(0x596B38 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
    RunTime::ResetMemoryContentAt(0x596B20 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // member count update
    RunTime::ResetMemoryContentAt(0x596BC8 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // group update
    RunTime::ResetMemoryContentAt(0x596B50 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // member type update
}