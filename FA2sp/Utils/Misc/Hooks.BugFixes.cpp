#include <Helpers/Macro.h>
#include <GlobalVars.h>

#include "../../Logger.h"

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

// No Easy View pls
DEFINE_HOOK(421BCE, CFinalSunDlg_Easyview, 6)
{
	return 0x421DBD;
}

// Make Cliff works on lunar
// Craaaaashes! Maybe FA2 hardcoded to use tileset 10?
//DEFINE_HOOK(4353B8, FA2Main_CliffToolForLunar_Back, 5)
//{
//	return 0x4353D0;
//}
//
//DEFINE_HOOK(435338, FA2Main_CliffToolForLunar_Front, 5)
//{
//	return 0x435350;
//}