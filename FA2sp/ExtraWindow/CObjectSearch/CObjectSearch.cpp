#include "CObjectSearch.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../FA2sp.h"

HWND CObjectSearch::m_hwnd;
CFinalSunDlg* CObjectSearch::m_parent;

BOOL CObjectSearch::JumpToCoord(CWnd* pWnd, int X, int Y)
{
    struct HelperView : public CView
    {
    public:
        int sub_4763D0(int a2, int a3)
            { JMP_THIS(0x4763D0); }
    };

    if (pWnd)
    {
        //HelperView* pIsoView = reinterpret_cast<HelperView*>(m_parent + 0x2158);
        HelperView* pIsoView = reinterpret_cast<HelperView*>(pWnd);
        int nHW = GlobalVars::CurrentMapWidthPlusHeight();
        int nParam = X + Y * nHW;
        RECT rect;
        ::GetWindowRect(pIsoView->GetSafeHwnd(), &rect);
        int v6 = (60 * (nParam % nHW)) / 4
            + (30 * (nParam / nHW)) / 2
            - 30
            * *(unsigned __int8*)(((nParam % nHW
                + nParam / nHW * nHW) << 6)
                + *reinterpret_cast<DWORD*>(0x7ACDB8)
                + 51)
            / 2;
        pIsoView->sub_4763D0(
            30 * (nHW + (nParam / nHW)) - (rect.right - rect.left) / 2 - (30 * (nParam % nHW)) - rect.left,
            v6 - (rect.bottom - rect.top) / 2 - rect.top
        );
        return ::RedrawWindow(pIsoView->GetSafeHwnd(), 0, 0, 0x101);
    }
    return FALSE;
}

//DEFINE_HOOK(4766A0, sub_4766A0, 6)
//{
//    GET(CWnd*, pWnd, ECX);
//    GET(int, nWP, EAX);
//    auto& doc = CINI::CurrentDocument();
//    CString lpWaypoint;
//    lpWaypoint.Format("%d", nWP);
//    int nCoord = doc.GetInteger("Waypoints", lpWaypoint, -1);
//    if (lpWaypoint == -1)
//        return 0;
//    R->EAX(CObjectSearch::JumpToCoord(pWnd, GET_COORD_X(nCoord), GET_COORD_Y(nCoord)));
//
//    return 0x4767A2;
//}