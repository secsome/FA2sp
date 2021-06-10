#include "CObjectSearch.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../FA2sp.h"

HWND CObjectSearch::m_hwnd;
CFinalSunDlg* CObjectSearch::m_parent;

void CObjectSearch::Create(CFinalSunDlg* pParent)
{
    m_parent = pParent;
    m_hwnd = CreateDialog(
        static_cast<HINSTANCE>(FA2sp::hInstance),
        MAKEINTRESOURCE(302),
        *pParent,
        CObjectSearch::DlgProc
    );
    if (m_hwnd)
        ::ShowWindow(m_hwnd, SW_SHOW);
    else
    {
        Logger::Error("Failed to create CObjectSearch.\n");
        m_parent = NULL;
    }
}

void CObjectSearch::MoveToCoord(CIsoView* pWnd, int X, int Y)
{
    if (pWnd)
        pWnd->MoveToCoord(X, Y);
}

void CObjectSearch::Initialize(HWND hWnd)
{

}

void CObjectSearch::Close(HWND hWnd)
{
    ::EndDialog(hWnd, NULL);
    CObjectSearch::m_hwnd = NULL;
    CObjectSearch::m_parent = NULL;
}

BOOL CObjectSearch::DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
    {
        CObjectSearch::Initialize(hwnd);
        return TRUE;
    }
    case WM_COMMAND:
    {
        WORD ID = LOWORD(wParam);
        WORD CODE = HIWORD(wParam);
        switch (ID)
        {
        default:
            break;
        }
        break;
    }
    case WM_CLOSE:
    {
        CObjectSearch::Close(hwnd);
        return TRUE;
    }

    }

    // Process this message through default handler
    return FALSE;
}
