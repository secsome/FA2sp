#include "CObjectSearch.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../FA2sp.h"

int CObjectSearch::sub_4B1BD0_mine(int nWaypoint)
{
    auto& doc = GlobalVars::INIFiles::CurrentDocument();
    CString lpWaypoint;
    lpWaypoint.Format("%d", nWaypoint);
    int nCoord = doc.GetInteger("Waypoints", lpWaypoint, -1);
    if (lpWaypoint == -1)
        return -1;
    CString lpMapSize = doc.GetString("Map", "Size");
    int nMapWidth, nMapHeight;
    if (STDHelpers::IsNullOrEmpty(lpMapSize))
        return -1;
    if (sscanf_s(lpMapSize, "%*d,%*d,%d,%d", &nMapWidth, &nMapHeight) != 2)
        return -1;
    return (nCoord / 1000) + (nCoord % 1000 * (nMapWidth + nMapHeight));
}

DEFINE_HOOK(4766B1, sub_4766A0_Func4766B1, 9)
{
    REF_STACK(int, nWaypoint, STACK_OFFS(0x28, -0x4));
    int tmp = CObjectSearch::sub_4B1BD0_mine(nWaypoint);
    if (tmp == -1)
        return 0;
    else
    {
        R->EAX<int>(tmp);
        nWaypoint = tmp;
        return 0x4766BF;
    }
}