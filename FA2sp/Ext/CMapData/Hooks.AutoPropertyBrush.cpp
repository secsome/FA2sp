#include <Helpers/Macro.h>

#include "../CIsoView/Body.h"
#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(4B0186, CMapData_SetAircraftData_AutoPropertyBrush, 7)
{
	if (!CIsoViewExt::AutoPropertyBrush[0])
		return 0;

	GET_STACK(const int, nCellIndex, STACK_OFFS(0x160, -0x10));
	REF_STACK(CAircraftData, data, STACK_OFFS(0x160, 0x150));
	REF_STACK(ppmfc::CString, ID, STACK_OFFS(0x160, -0x8));
	REF_STACK(ppmfc::CString, House, STACK_OFFS(0x160, -0xC));

	data.TypeID = ID;
	data.House = House;
	data.X.Format("%d", CMapData::Instance->GetXFromCoordIndex(nCellIndex));
	data.Y.Format("%d", CMapData::Instance->GetYFromCoordIndex(nCellIndex));
	CViewObjectsExt::ApplyPropertyBrush_Aircraft(data);

	return 0x4B026A;
}

DEFINE_HOOK(4ACCE2, CMapData_SetBuildingData_AutoPropertyBrush, 6)
{
	if (!CIsoViewExt::AutoPropertyBrush[1])
		return 0;

	GET(const int, nCellIndex, EDI);
	REF_STACK(CBuildingData, data, STACK_OFFS(0x194, 0x184));
	REF_STACK(ppmfc::CString, ID, STACK_OFFS(0x194, -0x8));
	REF_STACK(ppmfc::CString, House, STACK_OFFS(0x194, -0xC));

	data.TypeID = ID;
	data.House = House;
	data.X.Format("%d", CMapData::Instance->GetXFromCoordIndex(nCellIndex));
	data.Y.Format("%d", CMapData::Instance->GetYFromCoordIndex(nCellIndex));
	CViewObjectsExt::ApplyPropertyBrush_Building(data);

	return 0x4ACE0E;
}

DEFINE_HOOK(4AC3E2, CMapData_SetInfantryData_AutoPropertyBrush, 6)
{
	if (!CIsoViewExt::AutoPropertyBrush[2])
		return 0;

	GET(const int, nCellIndex, ESI);
	REF_STACK(CInfantryData, data, STACK_OFFS(0x11C, 0x108));
	REF_STACK(const ppmfc::CString, ID, STACK_OFFS(0x11C, -0x8));
	REF_STACK(const ppmfc::CString, House, STACK_OFFS(0x11C, -0xC));

	data.TypeID = ID;
	data.House = House;
	data.X.Format("%d", CMapData::Instance->GetXFromCoordIndex(nCellIndex));
	data.Y.Format("%d", CMapData::Instance->GetYFromCoordIndex(nCellIndex));
	CViewObjectsExt::ApplyPropertyBrush_Infantry(data);

	return 0x4AC4ED;
}

DEFINE_HOOK(4B0C78, CMapData_SetUnitData_AutoPropertyBrush, 7)
{
	if (!CIsoViewExt::AutoPropertyBrush[3])
		return 0;

	GET_STACK(const int, nCellIndex, STACK_OFFS(0x178, -0x10));
	REF_STACK(CUnitData, data, STACK_OFFS(0x178, 0x168));
	REF_STACK(ppmfc::CString, ID, STACK_OFFS(0x178, -0x8));
	REF_STACK(ppmfc::CString, House, STACK_OFFS(0x178, -0xC));

	data.TypeID = ID;
	data.House = House;
	data.X.Format("%d", CMapData::Instance->GetXFromCoordIndex(nCellIndex));
	data.Y.Format("%d", CMapData::Instance->GetYFromCoordIndex(nCellIndex));
	CViewObjectsExt::ApplyPropertyBrush_Vehicle(data);

	return 0x4B0D7B;
}
