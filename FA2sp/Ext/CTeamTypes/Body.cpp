#include "Body.h"
void CTeamTypesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596D00 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // name update
	RunTime::ResetMemoryContentAt(0x596D30 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // veteran update
	RunTime::ResetMemoryContentAt(0x596D48 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // house update
	RunTime::ResetMemoryContentAt(0x596D60 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // priority update
	RunTime::ResetMemoryContentAt(0x596D78 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4); // max update
	RunTime::ResetMemoryContentAt(0x596D90 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // techlevel update
	RunTime::ResetMemoryContentAt(0x596DA8 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // group update
	RunTime::ResetMemoryContentAt(0x596DC0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // waypoint update
	RunTime::ResetMemoryContentAt(0x596DD8 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // script update
	RunTime::ResetMemoryContentAt(0x596DF0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // taskforce update
	RunTime::ResetMemoryContentAt(0x5970C0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // tag update
	RunTime::ResetMemoryContentAt(0x5970F0 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // transport waypoint update
	RunTime::ResetMemoryContentAt(0x597120 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4); // mind control decision update
}
