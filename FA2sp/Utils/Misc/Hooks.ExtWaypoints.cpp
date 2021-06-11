#include "../../FA2sp.h"

#include <MFC/ppmfc_cstring.h>

#include <string>

DEFINE_HOOK(4E5F30, String_To_Waypoint, 5)
{
    if (!ExtConfigs::ExtWaypoints)
        return 0;

	GET_STACK(char*, pString, 0x4);

	int n = 0;
	int len = strlen(pString);
	for (int i = len - 1, j = 1; i >= 0; i--, j *= 26)
	{
		int c = toupper(pString[i]);
		if (c < 'A' || c > 'Z') return 0;
		n += ((int)c - 64) * j;
	}
	R->EAX(n - 1);

	return 0x4E5F87;
}

DEFINE_HOOK(4E5F90, Waypoint_To_String, 7)
{
	if (!ExtConfigs::ExtWaypoints)
		return 0;

	GET_STACK(ppmfc::CString*, pString, 0x4);
	GET_STACK(int, nWaypoint, 0x8);

	if (nWaypoint == -1)
		pString->Format("0");
	else
	{
		std::string buffer;
		
		++nWaypoint;
		while (nWaypoint > 0)
		{
			int m = nWaypoint % 26;
			if (m == 0) m = 26;
			buffer = (char)(m + 64) + buffer;
			nWaypoint = (nWaypoint - m) / 26;
		}
		
		// Call the CTOR
		new(pString) ppmfc::CString(buffer.c_str());
	}

	R->EAX(pString);

	return 0x4E60FA;
}