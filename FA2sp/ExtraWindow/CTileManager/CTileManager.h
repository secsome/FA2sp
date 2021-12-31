#pragma once

#include <FA2PP.h>
#include <CTileSetBrowserFrame.h>

#include <vector>
#include <string>
#include <regex>

// A static window class
class CTileManager
{
public:
    enum { ListBox_Types = 6100, ListBox_Details = 6101 };

    static void Create(CTileSetBrowserFrame* pWnd);

    static HWND GetHandle()
        { return CTileManager::m_hwnd; }

    static void UpdateTypes(HWND hWnd);
    static void UpdateDetails(HWND hWnd, int kNode = -1);

protected:
    static void Initialize(HWND& hWnd);
    static void InitNodes();
    static void Close(HWND& hWnd);

    static BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    static void TypesProc(HWND hWnd, WORD nCode, LPARAM lParam);
    static void DetailsProc(HWND hWnd, WORD nCode, LPARAM lParam);

private:
    static HWND m_hwnd;
    static CTileSetBrowserFrame* m_parent;
    static std::vector<std::pair<std::string, std::regex>> Nodes;
    static std::vector<std::vector<int>> Datas;
};

