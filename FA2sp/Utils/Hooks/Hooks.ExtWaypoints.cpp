#include "../../FA2sp.h"

#include <MFC/ppmfc_cstring.h>
#include <GlobalVars.h>
#include <CINI.h>
#include <CTeamTypes.h>

#include <string>

class ExtWaypoint
{
public:
	static int String_To_Waypoint(const char* s)
	{
		int n = 0;
		int len = strlen(s);
		for (int i = len - 1, j = 1; i >= 0; i--, j *= 26)
		{
			int c = toupper(s[i]);
			if (c < 'A' || c > 'Z') return 0;
			n += ((int)c - 64) * j;
		}
		if (n <= 0)
			return -1;
		return n - 1;
	}

	static std::string Waypoint_To_String(int n)
	{
		if (n < 0)
			return "0";
		else
		{
			std::string buffer;
			++n;
			while (n> 0)
			{
				int m = n% 26;
				if (m == 0) m = 26;
				buffer = (char)(m + 64) + buffer;
				n = (n- m) / 26;
			}
			return buffer;
		}
	}
};

DEFINE_HOOK(4E5F30, String_To_Waypoint, 5)
{
    if (!ExtConfigs::ExtWaypoints)
        return 0;

	GET_STACK(const char*, pString, 0x4);

	R->EAX(ExtWaypoint::String_To_Waypoint(pString));

	return 0x4E5F87;
}

DEFINE_HOOK(4E5F90, Waypoint_To_String, 7)
{
	if (!ExtConfigs::ExtWaypoints)
		return 0;

	GET_STACK(ppmfc::CString*, pString, 0x4);
	GET_STACK(int, nWaypoint, 0x8);

	new(pString) ppmfc::CString(ExtWaypoint::Waypoint_To_String(nWaypoint).c_str());

	R->EAX(pString);

	return 0x4E60FA;
}

DEFINE_HOOK(4E97F4, CTeamTypes_OnCBCurrentTeamSelectChanged_String_To_Waypoint_1, 5)
{
	if (!ExtConfigs::ExtWaypoints)
		return 0;

	GET(CTeamTypes*, pThis, EBP);
	REF_STACK(ppmfc::CString, lpWaypoint, STACK_OFFS(0x178, 0x160));

	const int wp = ExtWaypoint::String_To_Waypoint(lpWaypoint);
	if (wp != -1)
		pThis->CString_Waypoint.Format("%d", wp);
	else
		pThis->CString_Waypoint = "";

	return 0x4E9890;
}

DEFINE_HOOK(4E9959, CTeamTypes_OnCBCurrentTeamSelectChanged_String_To_Waypoint_2, 5)
{
	if (!ExtConfigs::ExtWaypoints)
		return 0;

	GET(CTeamTypes*, pThis, EBP);
	REF_STACK(ppmfc::CString, lpWaypoint, STACK_OFFS(0x178, 0x128));

	const int wp = ExtWaypoint::String_To_Waypoint(lpWaypoint);
	if (wp != -1)
		pThis->CString_TransportWaypoint.Format("%d", wp);
	else
		pThis->CString_TransportWaypoint = "None";

	return 0x4E9A44;
}