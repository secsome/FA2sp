#pragma once

#include <CMapData.h>

#include <vector>

struct OverlayTypeData
{
    bool Rock;
};

class CMapDataExt : public CMapData
{
public:
    static CMapDataExt* GetExtension()
    {
        return reinterpret_cast<CMapDataExt*>(&CMapData::Instance());
    }

    bool ResizeMapExt(MapRect* const pRect);
    
    enum OreType { Riparius = 0, Cruentus, Vinifera, Aboreus };
    int GetOreValue(unsigned char nOverlay, unsigned char nOverlayData);
    int GetOreValueAt(CellData& cell);
    void InitOreValue();

    static std::vector<OverlayTypeData> OverlayTypeDatas;
    static int OreValue[4];
};