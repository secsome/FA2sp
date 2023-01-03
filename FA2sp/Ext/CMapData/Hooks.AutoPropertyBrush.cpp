#include <Helpers/Macro.h>

#include "../CIsoView/Body.h"
#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(4B026A, CMapData_SetAircraftData_AutoPropertyBrush, 5)
{
	if (CIsoViewExt::AutoPropertyBrush[0])
	{
		REF_STACK(CAircraftData, data, STACK_OFFS(0x160, 0x150));
		CViewObjectsExt::ApplyPropertyBrush_Aircraft(data);
	}
	
	return 0;
}

DEFINE_HOOK(4ACE0E, CMapData_SetBuildingData_AutoPropertyBrush, 5)
{
	if (CIsoViewExt::AutoPropertyBrush[1])
	{
		REF_STACK(CBuildingData, data, STACK_OFFS(0x194, 0x184));
		CViewObjectsExt::ApplyPropertyBrush_Building(data);
	}

	return 0;
}

DEFINE_HOOK(4AC4ED, CMapData_SetInfantryData_AutoPropertyBrush, 9)
{
	if (CIsoViewExt::AutoPropertyBrush[2])
	{
		REF_STACK(CInfantryData, data, STACK_OFFS(0x11C, 0x108));
		CViewObjectsExt::ApplyPropertyBrush_Infantry(data);
	}

	return 0;
}

DEFINE_HOOK(4B0D7B, CMapData_SetUnitData_AutoPropertyBrush, 5)
{
	if (CIsoViewExt::AutoPropertyBrush[3])
	{
		REF_STACK(CUnitData, data, STACK_OFFS(0x178, 0x168));
		CViewObjectsExt::ApplyPropertyBrush_Vehicle(data);
	}
	
	return 0;
}
