#pragma once

#include <CMapData.h>

class CMapDataExt : public CMapData
{
public:
    static CMapDataExt* GetExtension()
    {
        return reinterpret_cast<CMapDataExt*>(&CMapData::Instance());
    }

    bool ResizeMapExt(MapRect* const pRect);
    
    enum OreType { Riparius = 0, Cruentus, Vinifera, Aboreus };
    int GetOreValueAt(CellData& cell);
    void InitOreValue();

    static int OreValue[4];
};