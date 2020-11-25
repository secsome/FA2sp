#include "Body.h"

// Fix on wrong infantry facing
DEFINE_HOOK(473E46, CIsoView_UpdatePaint_InfantryFacing, 9)
{
	GET(int, Facing, EAX);
	R->EAX(7 - Facing / 32);
	R->ECX(R->lea_Stack<DWORD>(0x590));
	return 0x473E52;
}

//DEFINE_HOOK(4808A0, CIsoView_DrawImage_DEBUG, 5)
//{
//	GET_STACK(DWORD, dwCallerAddress, 0x0);
//	REF_STACK(const char*, regName, 0x4);
//	Logger::Debug("CIsoView_CreateImage Caller = %p, regName = %s\n", dwCallerAddress, regName);
//	if (strcmp(regName, "YAPOWR") == 0)
//	{
//		strcpy_s((char*)regName, 7, "GAPOWR");
//	}
//	return 0;
//}