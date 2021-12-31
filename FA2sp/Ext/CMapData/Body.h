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
};