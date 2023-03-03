#pragma once

#include <CMapData.h>

#include <vector>

struct OverlayTypeData
{
    bool Rock;
};

struct BuildingDataExt
{
    ~BuildingDataExt()
    {
        if (Foundations)
            delete Foundations;
        if (LinesToDraw)
            delete LinesToDraw;
    }

    bool IsCustomFoundation() const
    {
        return Foundations != nullptr;
    }

    int Width{ 0 };
    int Height{ 0 };
    std::vector<MapCoord>* Foundations{ nullptr };
    std::vector<std::pair<MapCoord, MapCoord>>* LinesToDraw{ nullptr };
};

class CMapDataExt : public CMapData
{
public:
    static CMapDataExt* GetExtension()
    {
        return reinterpret_cast<CMapDataExt*>(&CMapData::Instance());
    }

    void PackExt(bool UpdatePreview, bool Description);
    bool ResizeMapExt(MapRect* const pRect);
    
    enum OreType { Riparius = 0, Cruentus, Vinifera, Aboreus };
    int GetOreValue(unsigned char nOverlay, unsigned char nOverlayData);
    int GetOreValueAt(CellData& cell);
    void InitOreValue();

    void InitializeBuildingTypesExt(const char* ID);

    static std::vector<BuildingDataExt> BuildingDataExts;
    static std::vector<OverlayTypeData> OverlayTypeDatas;
    static int OreValue[4];
};