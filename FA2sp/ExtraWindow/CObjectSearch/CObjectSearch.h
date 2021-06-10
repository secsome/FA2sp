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

    static void MoveToCoord(CIsoView* pWnd, int X, int Y);

protected:
    static void Initialize(HWND hWnd);
    static void Close(HWND hWnd);

    static BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
    static HWND m_hwnd;
    static CFinalSunDlg* m_parent;
};