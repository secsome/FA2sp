#include "Body.h"

#include "../../Miscs/SaveMap.h"

#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>

#include <algorithm>
#include <vector>
#include <format>

int CMapDataExt::OreValue[4] { -1,-1,-1,-1 };
std::vector<OverlayTypeData> CMapDataExt::OverlayTypeDatas;
std::vector<BuildingDataExt> CMapDataExt::BuildingDataExts;

int CMapDataExt::GetOreValue(unsigned char nOverlay, unsigned char nOverlayData)
{
    if (nOverlay >= 0x66 && nOverlay <= 0x79)
        return nOverlayData * OreValue[OreType::Riparius];
    else if (nOverlay >= 0x1B && nOverlay <= 0x26)
        return nOverlayData * OreValue[OreType::Cruentus];
    else if (nOverlay >= 0x7F && nOverlay <= 0x92)
        return nOverlayData * OreValue[OreType::Vinifera];
    else if (nOverlay >= 0x93 && nOverlay <= 0xA6)
        return nOverlayData * OreValue[OreType::Aboreus];
    else
        return 0;
}

int CMapDataExt::GetOreValueAt(CellData& cell)
{
    return GetOreValue(cell.Overlay, cell.OverlayData);
}

void CMapDataExt::InitOreValue()
{
    OreValue[OreType::Aboreus] = CINI::Rules->GetInteger("Aboreus", "Value");
    OreValue[OreType::Cruentus] = CINI::Rules->GetInteger("Cruentus", "Value");
    OreValue[OreType::Riparius] = CINI::Rules->GetInteger("Riparius", "Value");
    OreValue[OreType::Vinifera] = CINI::Rules->GetInteger("Vinifera", "Value");
}