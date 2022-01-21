#include "Body.h"

#include "../../Miscs/SaveMap.h"

#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>

#include <algorithm>
#include <vector>
#include <format>

int CMapDataExt::OreValue[4] { -1,-1,-1,-1 };
std::vector<OverlayTypeData> CMapDataExt::OverlayTypeDatas;

int CMapDataExt::GetOreValueAt(CellData& cell)
{
    if (cell.Overlay >= 0x66 && cell.Overlay <= 0x79)
        return OreValue[OreType::Riparius];
    if (cell.Overlay >= 0x1B && cell.Overlay <= 0x26)
        return OreValue[OreType::Cruentus];
    if (cell.Overlay >= 0x7F && cell.Overlay <= 0x92)
        return OreValue[OreType::Vinifera];
    if (cell.Overlay >= 0x93 && cell.Overlay <= 0xA6)
        return OreValue[OreType::Aboreus];
    return 0;
}

void CMapDataExt::InitOreValue()
{
    OreValue[OreType::Aboreus] = CINI::Rules->GetInteger("Aboreus", "Value");
    OreValue[OreType::Cruentus] = CINI::Rules->GetInteger("Cruentus", "Value");
    OreValue[OreType::Riparius] = CINI::Rules->GetInteger("Riparius", "Value");
    OreValue[OreType::Vinifera] = CINI::Rules->GetInteger("Vinifera", "Value");
}