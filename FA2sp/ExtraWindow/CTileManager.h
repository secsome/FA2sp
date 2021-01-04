#pragma once

#include <FA2PP.h>
#include <CTileSetBrowserFrame.h>

#include <array>
#include <vector>

// A static window class
class CTileManager
{
public:
    enum {
        Nodes_Cliff = 0, Nodes_Water, Nodes_Ramp, Nodes_Bridge,
        Nodes_Road, Nodes_Feature, Nodes_Rail, Nodes_Tunnel, Nodes_Shore,
        Nodes_Pave, Nodes_Fix, Nodes_LAT, Nodes_Other, Nodes_Count, Nodes_RemoveFlag = -1
    };

    enum { ListBox_Types = 6100, ListBox_Details = 6101 };

    using data_type = std::array<std::vector<int>, Nodes_Count>;
    using node_type = std::array<const char*, Nodes_Count>;

    static void Create(CTileSetBrowserFrame* pWnd);

    static HWND GetHandle()
        { return CTileManager::m_hwnd; }

    static void UpdateTypes(HWND hWnd);
    static void UpdateDetails(HWND hWnd, int kNode = Nodes_RemoveFlag);

protected:
    static void Initialize(HWND& hWnd);
    static void Close(HWND& hWnd);

    static BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    static void TypesProc(HWND hWnd, WORD nCode, LPARAM lParam);
    static void DetailsProc(HWND hWnd, WORD nCode, LPARAM lParam);

private:
    static HWND m_hwnd;
    static CTileSetBrowserFrame* m_parent;
    static node_type Nodes;
    static data_type Datas;
};

