#include "Body.h"

#include <GlobalVars.h>

#include <Windows.h>

//DEFINE_HOOK(470A66, DEBUGGGGASD, 7)
//{
//	// DEBUG USE
//
//	auto dbgmap = reinterpret_cast<FAMap<CString, CString, 0x5D8CD0, 0>*>(0x72A870);
//	Logger::Debug("dbgmap size = %d\n", dbgmap->size());
//	for (auto& x : *dbgmap)
//	{
//		Logger::Debug("%s\n", x.first);
//	}
//	return 0;
//}

DEFINE_HOOK(45AF03, CIsoView_StatusBar_YXTOXY_YToX_1, 7)
{
	GET_STACK(int, nPointX, 0x30);
	R->EDI(nPointX);
	R->ECX(R->lea_Stack<DWORD>(0x458));
	return 0x45AF0A;
}

DEFINE_HOOK(45AF21, CIsoView_StatusBar_YXTOXY_YToX_2, 7)
{
	GET_STACK(int, nPointY, 0x38);
	R->EDI(nPointY);
	return 0;
}

DEFINE_HOOK(45AF44, CIsoView_StatusBar_YXTOXY_XToY_1, 7)
{
	GET_STACK(int, nPointY, 0x38);
	R->EBX(nPointY);
	R->EAX(R->lea_Stack<DWORD>(0x458));
	return 0x45AF4B;
}

DEFINE_HOOK(45AF57, CIsoView_StatusBar_YXTOXY_XToY_2, 7)
{
	GET_STACK(int, nPointX, 0x30);
	R->EBX(nPointX);
	return 0;
}

// Fix on wrong infantry facing
DEFINE_HOOK(473E46, CIsoView_UpdatePaint_InfantryFacing, 9)
{
	GET(int, Facing, EAX);
	R->EAX(7 - Facing / 32);
	R->ECX(R->lea_Stack<DWORD>(0x590));
	return 0x473E52;
}

DEFINE_HOOK(46CB96, CIsoView_UpdateOverlay_AutoConnect_1, 5)
{
	CIsoView::sub_469B20(R->EBP(), R->EBX());
	return 0x46CBD3;
}

DEFINE_HOOK(469A69, CIsoView_UpdateOverlay_AutoConnect_2, 8)
{
	GET(unsigned char, nOverlayIndex, ESI);
	GET(bool, bConnectAsWall, ECX);
	if (bConnectAsWall)
		return 0x469A71;
	if (nOverlayIndex >= 0 && nOverlayIndex <= 255)
	{
		auto& rules = GlobalVars::INIFiles::Rules();
		CString key;
		key.Format("%d", nOverlayIndex);
		auto pRegName = rules.GetString("OverlayTypes", key, "");
		bool bWall = rules.GetBool(pRegName, "Wall", false);
		if (bWall)
			return 0x469A71;
	}
	return 0x469B07;
}