#pragma once

#include <FA2PP.h>

// A static window class
class CTileManager
{
public:
    static void Create(HWND hParent);

    static HWND GetHandle()
        { return CTileManager::m_hwnd; }

protected:
    static void Initialize(HWND& hWnd);
    static void Close(HWND& hWnd);
    
    static BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    static void TypesProc(WORD nCode, LPARAM lParam);
    static void DetailsProc(WORD nCode, LPARAM lParam);

    static void UpdateDetails(int id);

private:
    static HWND m_hwnd;

    enum {ListBoxTypes = 6100, ListBoxDetails = 6101};
};

