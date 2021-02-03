#pragma once

#include <FA2PP.h>
#include <CFinalSunDlg.h>

// Another static window class
class CObjectSearch
{
public:
    static HWND GetHandle()
        { return CObjectSearch::m_hwnd; }
    static void Create(CFinalSunDlg* pParent);

    // TODO
    static BOOL JumpToCoord(CWnd* pWnd, int X, int Y);

private:
    static HWND m_hwnd;
    static CFinalSunDlg* m_parent;
};