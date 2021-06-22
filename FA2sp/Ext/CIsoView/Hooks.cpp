#include "Body.h"
#include "../../FA2sp.h"

#include <GlobalVars.h>
#include <CINI.h>

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
	// static int __stdcall sub_469B20(int Y, int X);
	int X = R->EBX();
	int Y = R->EBP();
	PUSH_VAR32(X);
	PUSH_VAR32(Y);
	CALL(0x469B20);
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
		ppmfc::CString key;
		key.Format("%d", nOverlayIndex);
		auto pRegName = rules.GetString("OverlayTypes", key, "");
		bool bWall = rules.GetBool(pRegName, "Wall", false);
		if (bWall)
			return 0x469A71;
	}
	return 0x469B07;
}

DEFINE_HOOK(459F4F, CIsoView_Draw_CopySelectionBoundColor, 6)
{
	R->Stack<COLORREF>(0x0, ExtConfigs::CopySelectionBound_Color);
	return 0;
}

DEFINE_HOOK(45AD81, CIsoView_Draw_CursorSelectionBoundColor, 5)
{
	R->Stack<COLORREF>(0x0, ExtConfigs::CursorSelectionBound_Color);
	return 0;
}

DEFINE_HOOK(45ADD0, CIsoView_Draw_CursorSelectionBoundHeightColor, 6)
{
	R->Stack<COLORREF>(0x8, ExtConfigs::CursorSelectionBound_HeightColor);
	return 0;
}

DEFINE_HOOK(474A49, CIsoView_Draw_WaypointColor, 5)
{
	GET(CIsoView*, pThis, EBP);
	GET(int, X, ESI);
	GET(int, Y, EDI);
	GET_STACK(CString, s, STACK_OFFS(0xD18, 0xCE4));

	pThis->DrawText(X + 15, Y + 7, s, ExtConfigs::Waypoint_Color);

	return 0x474A67;
}

DEFINE_HOOK(4685EA, CIsoView_DrawText, 9)
{
	if (ExtConfigs::Waypoint_Background)
	{
		GET(HDC, hdc, EDX);

		SetBkColor(hdc, ExtConfigs::Waypoint_Background_Color);
		SetBkMode(hdc, OPAQUE);

		return 0x4685F3;
	}
	return 0;
}