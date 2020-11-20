#include <Helpers/Macro.h>

#include "../../Logger.h"

// FA2 will no longer automatically change the extension of map
DEFINE_HOOK(42703A, FA2Main_SaveMap_Extension, 9)
{
	return 0x42708D;
}


// Make FA2 use path stored in FinalAlert.ini instead of Reg
DEFINE_HOOK(41FD8A, FA2Main_GetFilePath_1, 6)
{
	return 0x41FD90;
}

DEFINE_HOOK(41FDDB, FA2Main_GetFilePath_2, 6)
{
	return 0x41FDE9;
}

// No Easy View pls
DEFINE_HOOK(421BCE, FA2Main_Easyview, 6)
{
	return 0x421DBD;
}

// Fix on wrong infantry facing
DEFINE_HOOK(473E46, CIsoView_UpdatePaint_InfantryFacing, 9)
{
	GET(int, Facing, EAX);
	R->EAX(7 - Facing / 32);
	R->ECX(R->lea_Stack<DWORD>(0x590));
	return 0x473E52;
}

//DEFINE_HOOK(4808A0, CIsoView_DrawSHP_DEBUG, 5)
//{
//	GET_STACK(DWORD, dwCallerAddress, 0x0);
//	GET_STACK(const char*, shpName, 0x4);
//	Logger::Debug("CIsoView_DrawSHP Caller = %p, shpName = %s\n", dwCallerAddress, shpName);
//	return 0;
//}

////Make cliff tools work in lunar as well
//DEFINE_HOOK(435370, FA2Main_LunarCliff_Debug, 6)
//{
//	GET_STACK(DWORD, dwCallerAddress, 0x0);
//	Logger::Debug(__FUNCTION__" Caller = %P\n", dwCallerAddress);
//	return 0;
//}
//
//DEFINE_HOOK_AGAIN(4352F0, FA2Main_LunarCliff_Debug, 6);