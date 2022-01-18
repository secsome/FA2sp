#include "Body.h"

#include "../../Miscs/SaveMap.h"

#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>

#include <algorithm>
#include <vector>
#include <format>

int CMapDataExt::OreValue[4] { -1,-1,-1,-1 };

bool CMapDataExt::ResizeMapExt(MapRect* const pRect)
{
    this->UpdateCurrentDocument();

    const int nNewWidth = pRect->Width;
    const int nNewHeight = pRect->Height;

    const int nOldWidth = this->Size.Width;
    const int nOldHeight = this->Size.Height;
 
    if (nNewWidth < nOldWidth ||
        nNewHeight < nOldHeight ||
        nNewWidth - nOldWidth < pRect->Left ||
        nNewHeight - nOldHeight < pRect->Top)
        return false;
    
    const int nOldMapMagic = this->MapWidthPlusHeight;
    const int nOldCellDataCount = this->CellDataCount;
    auto pOldCellDatas = this->CellDatas;

    MapCoord coordToMove =
        MapCoord::Facings[FACING_EAST] * pRect->Left +
        MapCoord::Facings[FACING_SOUTH] * pRect->Top +
        MapCoord::Facings[FACING_SOUTHWEST] * (nNewWidth - nOldWidth);

    // Clear UndoRedoDatas
    for (int i = 0; i < this->UndoRedoDataCount; ++i)
    {
        GameDelete(this->UndoRedoData[i].Pointer_10);
        GameDelete(this->UndoRedoData[i].Pointer_14);
        GameDelete(this->UndoRedoData[i].Pointer_18);
        GameDelete(this->UndoRedoData[i].Pointer_1C);
        GameDelete(this->UndoRedoData[i].Pointer_20);
        GameDelete(this->UndoRedoData[i].Pointer_24);
        GameDelete(this->UndoRedoData[i].Pointer_28);
        GameDelete(this->UndoRedoData[i].Pointer_2C);
    }
    GameDelete(this->UndoRedoData);
    this->UndoRedoCurrentDataIndex = -1;
    this->UndoRedoData = nullptr;
    this->UndoRedoDataCount = 0;

    this->CellDatas = nullptr;
    this->CellDataCount = 0;

    memset(this->Overlay, 0xFF, sizeof(this->Overlay));
    memset(this->OverlayData, 0, sizeof(this->OverlayData));

    // update the size
    CINI::CurrentDocument->WriteString("Map", "Size", std::format("0,0,{},{}", nNewWidth, nNewHeight).c_str());
    CINI::CurrentDocument->WriteString("Map", "LocalSize", std::format("2,4,{},{}", nNewWidth - 4, nNewHeight - 6).c_str());

    this->Size.Left = 0;
    this->Size.Top = 0;
    this->Size.Width = nNewWidth;
    this->Size.Height = nNewHeight;

    this->LocalSize.Left = 2;
    this->LocalSize.Top = 4;
    this->LocalSize.Width = nNewWidth - 4;
    this->LocalSize.Height = nNewHeight - 6;

    this->MapWidthPlusHeight = nNewWidth + nNewHeight;

    this->CellDataCount = (this->MapWidthPlusHeight + 1) * (this->MapWidthPlusHeight + 1);
    this->CellDatas = GameCreateVector<CellData>(this->CellDataCount);

    GameDelete(this->IsoPackData);
    this->IsoPackData = nullptr;
    this->IsoPackDataCount = 0;
    
    // updating objects in the vector
    std::for_each(this->InfantryDatas.begin(), this->InfantryDatas.end(), 
        [coordToMove](CInfantryData& item)
        {
            int x = atoi(item.X) + coordToMove.X;
            int y = atoi(item.Y) + coordToMove.Y;
            item.X.Format("%d", x);
            item.Y.Format("%d", y);
        });
    std::for_each(this->StructureDatas.begin(), this->StructureDatas.end(), 
        [coordToMove](StructureData& item)
        {
            item.X += coordToMove.X;
            item.Y += coordToMove.Y;
        });
    std::for_each(this->TerrainDatas.begin(), this->TerrainDatas.end(), 
        [coordToMove](CTerrainData& item)
        {
            item.X += coordToMove.X;
            item.Y += coordToMove.Y;
        });
    std::for_each(this->TubeDatas.begin(), this->TubeDatas.end(),
        [coordToMove](TubeData& item) {
            item.EnterX += coordToMove.X;
            item.ExitX += coordToMove.X;
            item.EnterY += coordToMove.Y;
            item.ExitY += coordToMove.Y;
        });
    
    // updating objects in the ini
    auto UpdateObjectsInINIValue = [&](const char* lpSection, int nPos)
    {
        if (auto pSection = CINI::CurrentDocument->GetSection(lpSection))
        {
            std::vector<ppmfc::CString> itemsToRemove;
            for (auto& pair : pSection->GetEntities())
            {
                int nLen = pair.second.GetLength();
                int nStart, nEnd = -1;
                for (int i = 0, cnt = 0; i < nLen; ++i)
                {
                    if (pair.second[i] == ',')
                        ++cnt;

                    if (cnt == nPos)
                    {
                        if (nPos == 0) // For Tubes
                            nStart = 0;
                        else
                            nStart = i + 1;
                        cnt = 0;
                        for (int j = nStart; j < nLen; ++j)
                        {
                            if (pair.second[j] == ',')
                                ++cnt;

                            if (cnt == 2)
                            {
                                nEnd = j;
                                break;
                            }
                        }

                        if (nEnd != -1) // do process
                        {
                            auto prefix = pair.second.Mid(0, nStart);
                            auto suffix = pair.second.Mid(nEnd);
                            auto midpart = pair.second.Mid(nStart, nEnd - nStart);
                            int x, y;
                            if (sscanf_s(midpart, "%d,%d", &x, &y) == 2)
                            {
                                x += coordToMove.X;
                                y += coordToMove.Y;
                                /*if (!this->IsCoordInMap(x, y))
                                    itemsToRemove.push_back(pair.first);
                                else*/
                                {
                                    midpart.Format("%d,%d", x, y);
                                    pair.second = prefix + midpart + suffix;
                                }
                            }
                            break;
                        }
                        
                    }
                }
            }
            for (auto& item : itemsToRemove)
                CINI::CurrentDocument->DeleteKey(pSection, item);
        }
    };
    UpdateObjectsInINIValue("Aircraft", 3);
    UpdateObjectsInINIValue("Infantry", 3);
    UpdateObjectsInINIValue("Units", 3);
    UpdateObjectsInINIValue("Structures", 3);
    UpdateObjectsInINIValue("Smudge", 1);
    UpdateObjectsInINIValue("Tubes", 0); // EnterPos
    UpdateObjectsInINIValue("Tubes", 3); // ExitPos

    auto UpdateObjectsInINIKey = [&](const char* lpSection)
    {
        std::map<MapCoord, std::string> values;
        if (auto pSection = CINI::CurrentDocument->GetSection(lpSection))
        {
            for (auto& pair : pSection->GetEntities())
            {
                MapCoord buffer;
                buffer.X = atoi(pair.first);
                buffer.Y = buffer.X / 1000;
                buffer.X %= 1000;

                buffer.X += coordToMove.X;
                buffer.Y += coordToMove.Y;

                //if(this->IsCoordInMap(buffer.X, buffer.Y))
                    values[buffer] = pair.second.m_pchData;
            }
        }
        CINI::CurrentDocument->DeleteSection(lpSection);
        if (auto pSection = CINI::CurrentDocument->AddSection(lpSection))
        {
            for (auto& value : values)
            {
                char buffer[8];
                _itoa(value.first.X + value.first.Y * 1000, buffer, 10);
                CINI::CurrentDocument->WriteString(pSection, buffer, value.second.c_str());
            }
        }
        values.clear();
    };
    UpdateObjectsInINIKey("CellTags");
    UpdateObjectsInINIKey("Terrain");

    if (auto pSection = CINI::CurrentDocument->GetSection("Waypoints"))
    {
        std::vector<ppmfc::CString> itemsToRemove;
        for (auto& pair : pSection->GetEntities())
        {
            MapCoord value;
            value.X = atoi(pair.second);
            value.Y = value.X / 1000;
            value.X %= 1000;

            value.X += coordToMove.X;
            value.Y += coordToMove.Y;

            /*if (!this->IsCoordInMap(value.X, value.Y))
                itemsToRemove.push_back(pair.first);
            else*/
                pair.second.Format("%d", value.X + value.Y * 1000);
        }

        for (auto& item : itemsToRemove)
            CINI::CurrentDocument->DeleteKey(pSection, item);
    }

    auto CopyCellData = [&](int x, int y)
    {
        int nOldIndex = x * nOldMapMagic + y;
        int nNewIndex = (x + coordToMove.X) * this->MapWidthPlusHeight + y + coordToMove.Y;
        if (nNewIndex < this->CellDataCount && nNewIndex > this->MapWidthPlusHeight)
            this->CellDatas[nNewIndex] = pOldCellDatas[nOldIndex];
    };
    // Iterate the old map
    for (int i = 1; i <= nOldWidth; ++i)
    {
        if (i != nOldWidth)
        {
            for (int j = 1; j <= nOldHeight; ++j)
            {
                CopyCellData(i + j - 1, nOldWidth - i + j);
                CopyCellData(i + j, nOldWidth - i + j);
            }
        }
        else // Last specific column
        {
            for (int j = 1; j <= nOldHeight; ++j)
                CopyCellData(i + j - 1, nOldWidth - i + j);
        }
    }
    
    GameDeleteVector(pOldCellDatas);

    // need further investigation
    this->InitMinimap();

    this->UpdateFieldAircraftData(false);
    this->UpdateFieldInfantryData(false);
    this->UpdateFieldStructureData(false);
    this->UpdateFieldTerrainData(false);
    this->UpdateFieldUnitData(false);
    this->UpdateFieldWaypointData(false);
    this->UpdateFieldCelltagData(false);
    this->UpdateFieldTubeData(false);
    this->UpdateFieldSmudgeData(false);
    this->UpdateINIFile(SaveMapFlag::UpdatePreview);

    // Update the preview map manually
    // Now we use a slow way because I didn't find how to update it... for now
    for (int i = 1; i <= nNewWidth; ++i)
    {
        if (i != nNewWidth)
        {
            for (int j = 1; j <= nNewHeight; ++j)
            {
                this->UpdateMapPreviewAt(nNewWidth - i + j, i + j - 1);
                this->UpdateMapPreviewAt(nNewWidth - i + j, i + j);
            }
        }
        else // Last specific column
        {
            for (int j = 1; j <= nNewHeight; ++j)
                this->UpdateMapPreviewAt(nNewWidth - i + j, i + j - 1);
        }
    }

    /*std::string path = std::format("{}\\resized_map.map", CFinalSunApp::ExePath);
    SaveMapExt::IsAutoSaving = true;
    CFinalSunDlg::Instance->SaveMap(path.c_str());
    SaveMapExt::IsAutoSaving = false;

    MessageBox(
        NULL,
        std::format("Resized map has been saved to {}\n! FA2 need restarting before you can continue.", path).c_str(),
        "FA2sp",
        MB_OK);

    exit(0);*/

    return true;
}

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