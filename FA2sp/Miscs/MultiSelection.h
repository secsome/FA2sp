#pragma once

#include <CMapData.h>

#include <set>
#include <concepts>

class MultiSelection
{
public:
    inline static bool AddCoord(int X, int Y);
    inline static bool RemoveCoord(int X, int Y);
    inline static size_t GetCount();
    inline static void Clear();
    inline static void ReverseStatus(int X, int Y);
    inline static bool IsSelected(int X, int Y);

    struct MyClipboardData
    {
        int X;
        int Y;
        unsigned char Overlay;
        unsigned char OverlayData;
        unsigned short TileIndex;
        unsigned short TileIndexHiPart;
        unsigned char TileSubIndex;
        unsigned char Height;
        unsigned char IceGrowth;
        CellData::CellDataFlag Flag;
    };
    static void Copy();
    static void Paste(int X, int Y, int nBaseHeight, MyClipboardData* data, size_t length);

    template<typename _Fn> requires std::invocable<_Fn, CellData&>
    static void ApplyForEach(_Fn _Func)
    {
        for (auto& coord : SelectedCoords)
        {
            auto pCell = CMapData::Instance->GetCellAt(coord.X, coord.Y);
            _Func(*pCell);
        }
    }

    static bool ShiftKeyIsDown;
    static BGRStruct ColorHolder[0x1000];
    static MapCoord CurrentCoord;

private:
    static std::set<MapCoord> SelectedCoords;
};

