#include "CTileManager.h"

#include "../FA2sp.h"

HWND CTileManager::m_hwnd;

void CTileManager::Create(HWND hParent)
{
    m_hwnd = CreateDialog(
        static_cast<HINSTANCE>(FA2sp::hInstance),
        MAKEINTRESOURCE(301),
        hParent, // should be CTileBrowserFrame
        CTileManager::DlgProc
    );
    if (m_hwnd)
        ShowWindow(m_hwnd, SW_SHOW);
}

void CTileManager::Initialize(HWND& hWnd)
{
    
}

void CTileManager::Close(HWND& hWnd)
{
    EndDialog(hWnd, NULL);
    CTileManager::m_hwnd = NULL;
}

BOOL CALLBACK CTileManager::DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
    {
        CTileManager::Initialize(hwnd);
        return TRUE;
    }
    case WM_COMMAND:
    {
        WORD ID = LOWORD(wParam);
        WORD CODE = HIWORD(wParam);
        switch (ID)
        {
        case ListBoxTypes:
            CTileManager::TypesProc(CODE, lParam);
            break;
        case ListBoxDetails:
            CTileManager::DetailsProc(CODE, lParam);
            break;
        default:
            break;
        }
        break;
    }
    case WM_CLOSE:
    {
        CTileManager::Close(hwnd);
        return TRUE;
    }

    }

    // Process this message through default handler
    return FALSE;
}

void CTileManager::TypesProc(WORD nCode, LPARAM lParam)
{
    HWND hListBox = reinterpret_cast<HWND>(lParam);
    CListBox* pListBox = (CListBox*)CListBox::FromHandle(hListBox);
    if (pListBox->GetCount() <= 0)
        return;
    switch (nCode)
    {
    case LBN_SELCHANGE:
    case LBN_DBLCLK:

        break;
    default:
        break;
    }
}

void CTileManager::DetailsProc(WORD nCode, LPARAM lParam)
{
    HWND hListBox = reinterpret_cast<HWND>(lParam);
    CListBox* pListBox = (CListBox*)CListBox::FromHandle(hListBox);
    if (pListBox->GetCount() <= 0)
        return;


    HWND hParent = GetParent(CTileManager::GetHandle());
    HWND hTileComboBox = GetDlgItem(hParent, 1366);

    switch (nCode)
    {
    case LBN_SELCHANGE:
    case LBN_DBLCLK:
        break;
    default:
        break;
    }
}