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