#include <Helpers/Macro.h>
#include <GlobalVars.h>
#include <CMapData.h>

#include <MFC/ppmfc_cstring.h>

#include "../../FA2sp.h"

// FA2 will no longer automatically change the extension of map
DEFINE_HOOK(42703A, CFinalSunDlg_SaveMap_Extension, 9)
{
	return 0x42708D;
}


// Make FA2 use path stored in FinalAlert.ini instead of Reg
DEFINE_HOOK(41FD8A, CFinalSunDlg_GetFilePath_1, 6)
{
	return 0x41FD90;
}

DEFINE_HOOK(41FDDB, CFinalSunDlg_GetFilePath_2, 6)
{
	return 0x41FDE9;
}

// Extend Undo/Redo limit to INT_MAX
DEFINE_HOOK(4BBAB8, CMapData_sub_4BB990, 6)
{
	GET(CMapData*, pThis, EBX);

	++pThis->unknown_801D0;
	++pThis->unknown_801CC;

	R->ESI(pThis->unknown_801CC);

	if (pThis->unknown_801CC <= Constants::UndoRedoStep)	
		return 0x4BBBB7;

	R->EDX(pThis->UndoRedoData);
	pThis->unknown_801CC = Constants::UndoRedoStep;
	pThis->unknown_801D0 = Constants::UndoRedoStep - 1;
	return 0x4BBAF7;
}


// Self explained nameing
DEFINE_HOOK(421BCE, CFinalSunApp_InitInstance_NoEasyViewExplain, 6)
{
	return 0x421DBD;
}

// Fix the bug of SHP turret draws only one face
DEFINE_HOOK(483EA4, CLoading_LoadObjects_SHPTurretFix_1, 7)
{
    REF_STACK(int, nFacingCount, STACK_OFFS(0x868, 0x4C));
    // GET_STACK(bool, bIsBuilding, STACK_OFFS(0x868, 0x8C));
    GET_STACK(ppmfc::CString, pRegName, STACK_OFFS(0x868, -0x4));

    if (GlobalVars::INIFiles::Rules->GetBool(pRegName, "Turret"))
        nFacingCount = 8;
    else
        nFacingCount = 1;

    return 0x483EAB;
}

DEFINE_HOOK(483F9D, CLoading_LoadObjects_SHPTurretFix_2, 5)
{
    REF_STACK(int, nFlags, STACK_OFFS(0x868, 0x4C));
    GET_STACK(bool, bIsBuilding, STACK_OFFS(0x868, 0x8C));
    GET_STACK(ppmfc::CString, pRegName, STACK_OFFS(0x868, -0x4));

    if (GlobalVars::INIFiles::Rules->GetBool(pRegName, "Turret") && bIsBuilding)
        return 0x483FA4;
    else
        return 0x483FC2;
}