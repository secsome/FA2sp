#pragma once

#include <CMapData.h>

#include <unordered_map>
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

struct BuildingRenderData
{
    unsigned int HouseColor;
    ppmfc::CString ID;
    short X;
    short Y;
    short Facing;
    short Strength;
    unsigned char PowerUpCount;
    ppmfc::CString PowerUp1;
    ppmfc::CString PowerUp2;
    ppmfc::CString PowerUp3;
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

    static unsigned short CurrentRenderBuildingStrength;
    static std::unordered_map<int, BuildingDataExt> BuildingDataExts;
    static std::vector<BuildingRenderData> BuildingRenderDatasFix;
    static std::vector<OverlayTypeData> OverlayTypeDatas;
    static int OreValue[4];
};