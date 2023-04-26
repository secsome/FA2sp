#include "MultiSelection.h"

#include <CFinalSunDlg.h>
#include <CIsoView.h>
#include <Helpers/Macro.h>
#include <Drawing.h>
#include <CTileTypeClass.h>

#include "../Ext/CIsoView/Body.h"
#include "../Ext/CMapData/Body.h"

#include <algorithm>
#include <span>

// #include "../Source/CIsoView.h"

#include "../FA2sp.h"

std::set<MapCoord> MultiSelection::SelectedCoords;
bool MultiSelection::ShiftKeyIsDown = false;
BGRStruct MultiSelection::ColorHolder[0x1000];
MapCoord MultiSelection::CurrentCoord;

bool MultiSelection::AddCoord(int X, int Y)
{
    if (X == -1 || Y == -1)
        return false;

    MapCoord coord{ X,Y };
    auto itr = SelectedCoords.find(coord);
    if (itr == SelectedCoords.end())
    {
        SelectedCoords.insert(itr, coord);
        return true;
    }
    return false;
}

bool MultiSelection::RemoveCoord(int X, int Y)
{
    if (X == -1 || Y == -1)
        return false;

    MapCoord coord{ X,Y };
    auto itr = SelectedCoords.find(coord);
    if (itr != SelectedCoords.end())
    {
        SelectedCoords.erase(itr);
        return true;
    }
    return false;
}

size_t MultiSelection::GetCount()
{
    return SelectedCoords.size();
}

inline void MultiSelection::Clear()
{
    SelectedCoords.clear();
}

inline void MultiSelection::ReverseStatus(int X, int Y)
{
    MapCoord mapCoord{ X,Y };
    auto itr = SelectedCoords.find(mapCoord);
    if (itr == SelectedCoords.end())
        SelectedCoords.insert(mapCoord);
    else
        SelectedCoords.erase(itr);
}

inline bool MultiSelection::IsSelected(int X, int Y)
{
    return SelectedCoords.find(MapCoord{ X,Y }) != SelectedCoords.end();
}

void MultiSelection::Copy()
{
    std::vector<MyClipboardData> datas;
    for (const auto& coord : SelectedCoords)
    {
        auto pCell = CMapData::Instance->GetCellAt(coord.X, coord.Y);
        MyClipboardData data;
        data.X = coord.X;
        data.Y = coord.Y;
        data.Overlay = pCell->Overlay;
        data.OverlayData = pCell->OverlayData;
        data.TileIndex = pCell->TileIndex;
        data.TileIndexHiPart = pCell->TileIndexHiPart;
        data.TileSubIndex = pCell->TileSubIndex;
        data.Height = pCell->Height;
        data.IceGrowth = pCell->IceGrowth;
        data.Flag = pCell->Flag;
        datas.push_back(data);
    }

    auto hGlobal = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, 8 + sizeof(MyClipboardData) * datas.size());
    if (hGlobal == NULL)
    {
        MessageBox(NULL, "Error", "Failed to allocate global memory!", MB_OK);
        return;
    }

    auto pBuffer = GlobalLock(hGlobal);
    if (pBuffer == nullptr)
    {
        MessageBox(NULL, "Error", "Failed to lock hGlobal handle!", MB_OK);
        return;
    }
    while (GlobalUnlock(hGlobal))
        ;

    reinterpret_cast<int*>(pBuffer)[0] = 0; // Flag indicate this is multiselection
    reinterpret_cast<size_t*>(pBuffer)[1] = datas.size();
    memcpy(reinterpret_cast<char*>(pBuffer) + 8, datas.data(), sizeof(MyClipboardData) * datas.size());

    OpenClipboard(CFinalSunApp::Instance->m_pMainWnd->m_hWnd);
    EmptyClipboard();
    if (FALSE == SetClipboardData(CFinalSunApp::Instance->ClipboardFormat, hGlobal))
        MessageBox(NULL, "Failed to set clipboard data", "Error", 0);
    CloseClipboard();
}

void MultiSelection::Paste(int X, int Y, int nBaseHeight, MyClipboardData* data, size_t length)
{
    std::span<MyClipboardData> cells {data, data + length};
    
    RECT rect
    { 
        std::numeric_limits<LONG>::max(), 
        std::numeric_limits<LONG>::max(), 
        std::numeric_limits<LONG>::min(),
        std::numeric_limits<LONG>::min() 
    };
    for (const auto& cell : cells)
    {
        if (cell.X < rect.left)
            rect.left = cell.X;
        if (cell.X > rect.right)
            rect.right = cell.X;
        if (cell.Y < rect.top)
            rect.top = cell.Y;
        if (cell.Y > rect.bottom)
            rect.bottom = cell.Y;
    }

    const MapCoord center = { (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2 };

    auto lowest_height = std::numeric_limits<unsigned char>::min();
    for (const auto& cell : cells)
    {
        int offx = cell.X - center.X;
        int offy = cell.Y - center.Y;

        const auto pCell = CMapData::Instance->TryGetCellAt(X + offx, Y + offy);
        if (pCell->Height < lowest_height)
            lowest_height = pCell->Height;
    }

    nBaseHeight += lowest_height;
    for (const auto& cell : cells)
    {
        int offx = cell.X - center.X;
        int offy = cell.Y - center.Y;

        auto nCellIndex = CMapData::Instance->GetCoordIndex(X + offx, Y + offy);
        if (nCellIndex < 0 || nCellIndex >= CMapData::Instance->CellDataCount)
            continue;

        auto pCell = CMapData::Instance->GetCellAt(nCellIndex);
        
        CMapData::Instance->DeleteTiberium(pCell->Overlay, pCell->OverlayData);
        pCell->Overlay = cell.Overlay;
        pCell->OverlayData = cell.OverlayData;
        CMapData::Instance->AddTiberium(pCell->Overlay, pCell->OverlayData);
        
        pCell->TileIndex = cell.TileIndex;
        pCell->TileIndexHiPart = cell.TileIndexHiPart;
        pCell->TileSubIndex = cell.TileSubIndex;
        
        pCell->Height = std::clamp(cell.Height + nBaseHeight, 0, 14);

        pCell->IceGrowth = cell.IceGrowth;
        pCell->Flag = cell.Flag;

        CMapData::Instance->UpdateMapPreviewAt(X + offx, Y + offy);
    }
}

DEFINE_HOOK(456EFC, CIsoView_OnMouseMove_MultiSelect_ReverseStatus, 6)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET_STACK(UINT, eFlags, STACK_OFFS(0x3D528, -0x4));
    REF_STACK(const CPoint, point, STACK_OFFS(0x3D528, -0x8));

    if (CIsoView::CurrentCommand->Command == FACurrentCommand::Nothing)
    {
        if (CIsoView::ControlKeyIsDown && (eFlags & MK_LBUTTON))
        {
            auto coord = CIsoView::GetInstance()->GetCurrentMapCoord(point);
            if (MultiSelection::ShiftKeyIsDown ?
                MultiSelection::RemoveCoord(coord.X, coord.Y) :
                MultiSelection::AddCoord(coord.X, coord.Y))
            {
                CIsoView::GetInstance()->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            }
            return 0x456EB6;
        }
    }

    return 0;
}

DEFINE_HOOK(469470, CIsoView_OnKeyDown, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CIsoView*, pThis, ECX);
    GET_STACK(UINT, nChar, 0x4);

    if (nChar == 'D')
    {
        if (CIsoView::ControlKeyIsDown)
            MultiSelection::Clear();
        else
            CFinalSunApp::Instance->FlatToGround = !CFinalSunApp::Instance->FlatToGround;

        pThis->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    }
    else if (nChar == 'A')
        pThis->KeyboardAMode = !pThis->KeyboardAMode;
    else if (nChar == VK_CONTROL)
        CIsoView::ControlKeyIsDown = true;
    else if (nChar == VK_SHIFT)
        MultiSelection::ShiftKeyIsDown = true;

    R->EAX(pThis->Default());

    return 0x4694A9;
}

DEFINE_HOOK(46BC30, CIsoView_OnKeyUp, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CIsoView*, pThis, ECX);
    GET_STACK(UINT, nChar, 0x4);

    if (nChar == VK_CONTROL)
        CIsoView::ControlKeyIsDown = false;
    else if (nChar == VK_SHIFT)
        MultiSelection::ShiftKeyIsDown = false;

    R->EAX(pThis->Default());

    return 0x46BC46;
}

DEFINE_HOOK(46EAFA, CIsoView_Draw_TileCurrentCoord_1, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    MultiSelection::CurrentCoord.X = R->EBP();
    MultiSelection::CurrentCoord.Y = R->EBX();
    return 0;
}

DEFINE_HOOK(46F680, CIsoView_Draw_TileCurrentCoord_2, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    MultiSelection::CurrentCoord.X = R->EDI();
    MultiSelection::CurrentCoord.Y = R->EBP();
    return 0;
}

DEFINE_HOOK_AGAIN(46F0D6, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46F1B7, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46F438, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46F55F, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46FC2F, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46FD0A, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(46FF71, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK_AGAIN(470081, CIsoView_Draw_MultiSelect, 7)
DEFINE_HOOK(470710, CIsoView_Draw_MultiSelect, 7)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    if (MultiSelection::IsSelected(MultiSelection::CurrentCoord.X, MultiSelection::CurrentCoord.Y))
    {
        GET(BGRStruct*, pColors, ESI);
        GET(int, nCount, ECX);

        for (int i = 0; i < nCount; ++i)
        {
            MultiSelection::ColorHolder[i].R = 
                (pColors[i].R + reinterpret_cast<RGBClass*>(&ExtConfigs::MultiSelectionColor)->R) / 2;
            MultiSelection::ColorHolder[i].G = 
                (pColors[i].G + reinterpret_cast<RGBClass*>(&ExtConfigs::MultiSelectionColor)->G) / 2;
            MultiSelection::ColorHolder[i].B = 
                (pColors[i].B + reinterpret_cast<RGBClass*>(&ExtConfigs::MultiSelectionColor)->B) / 2;

        }

        R->ESI(MultiSelection::ColorHolder);
    }

    return 0;
}

DEFINE_HOOK(433DA0, CFinalSunDlg_Tools_RaiseSingleTile, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CFinalSunDlg*, pThis, ECX);

    if (CMapData::Instance->MapWidthPlusHeight)
    {
        if (MultiSelection::GetCount())
        {
            MultiSelection::ApplyForEach(
                [](CellData& cell) {
                    if (cell.Height < 14)
                        ++cell.Height;
                }
            );
            pThis->MyViewFrame.pIsoView->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        }
        else
        {
            if (CIsoView::CurrentCommand->Command != FACurrentCommand::RaiseSingleTile)
            {
                pThis->BrushSize.nCurSel = 0;
                pThis->BrushSize.UpdateData(FALSE);
                pThis->MyViewFrame.pIsoView->BrushSizeX = 1;
                pThis->MyViewFrame.pIsoView->BrushSizeY = 1;
            }
            pThis->PlaySound(CFinalSunDlg::FASoundType::Normal);
            CIsoView::CurrentCommand->Command = FACurrentCommand::RaiseSingleTile;
        }
    }
    else
        pThis->PlaySound(CFinalSunDlg::FASoundType::Error);

    return 0x433DB7;
}

DEFINE_HOOK(433D30, CFinalSunDlg_Tools_LowerSingleTile, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CFinalSunDlg*, pThis, ECX);

    if (CMapData::Instance->MapWidthPlusHeight)
    {
        if (MultiSelection::GetCount())
        {
            MultiSelection::ApplyForEach(
                [](CellData& cell) {
                    if (cell.Height > 0)
                        --cell.Height;
                }
            );
            pThis->MyViewFrame.pIsoView->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        }
        else
        {
            if (CIsoView::CurrentCommand->Command != FACurrentCommand::LowerSingleTile)
            {
                pThis->BrushSize.nCurSel = 0;
                pThis->BrushSize.UpdateData(FALSE);
                pThis->MyViewFrame.pIsoView->BrushSizeX = 1;
                pThis->MyViewFrame.pIsoView->BrushSizeY = 1;
            }
            pThis->PlaySound(CFinalSunDlg::FASoundType::Normal);
            CIsoView::CurrentCommand->Command = FACurrentCommand::LowerSingleTile;
        }
    }
    else
        pThis->PlaySound(CFinalSunDlg::FASoundType::Error);

    return 0x433D47;
}

DEFINE_HOOK(433F70, CFinalSunDlg_Tools_HideSingleField, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CFinalSunDlg*, pThis, ECX);

    if (CMapData::Instance->MapWidthPlusHeight)
    {
        if (MultiSelection::GetCount())
        {
            MultiSelection::ApplyForEach(
                [](CellData& cell) {
                    cell.Flag.IsHiddenCell = true;
                }
            );
            pThis->MyViewFrame.pIsoView->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        }
        else
            CIsoView::CurrentCommand->Command = FACurrentCommand::HideSingleField;

        pThis->PlaySound(CFinalSunDlg::FASoundType::Normal);
    }
    else
        pThis->PlaySound(CFinalSunDlg::FASoundType::Error);

    return 0x433F83;
}

DEFINE_HOOK(435F10, CFinalSunDlg_Tools_Copy, 7)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET(CFinalSunDlg*, pThis, ECX);

    pThis->PlaySound(CFinalSunDlg::FASoundType::Normal);

    if (MultiSelection::GetCount())
        MultiSelection::Copy();
    else
        CIsoView::CurrentCommand->Command = FACurrentCommand::TileCopy;

    return 0x435F24;
}

DEFINE_HOOK(4C3850, CMapData_PasteAt, 8)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    GET_STACK(const int, X, 0x4);
    GET_STACK(const int, Y, 0x8);
    GET_STACK(const char, nBaseHeight, 0xC);

    OpenClipboard(CFinalSunApp::Instance->m_pMainWnd->m_hWnd);
    HANDLE hData = GetClipboardData(CFinalSunApp::Instance->ClipboardFormat);
    auto ptr = GlobalLock(hData);
    
    if (ptr)
    {
        if (reinterpret_cast<int*>(ptr)[0] == 0) // Multiselection
        {
            const auto length = reinterpret_cast<size_t*>(ptr)[1];
            const auto p = reinterpret_cast<MultiSelection::MyClipboardData*>(reinterpret_cast<char*>(ptr) + 8);
            MultiSelection::Paste(X, Y, nBaseHeight, p, length);
            GlobalUnlock(hData);
            CloseClipboard();
            return 0x4C388B;
        }
        else // Default selection
        {
            GlobalUnlock(hData);
            CloseClipboard();
            return 0;
        }
    }

    CloseClipboard();
    return 0x4C388B;
}

DEFINE_HOOK(474FE0, CIsoView_Draw_MultiSelectionMoney, 5)
{
    if (CIsoViewExt::DrawMoneyOnMap)
    {
        GET_STACK(HDC, hDC, STACK_OFFS(0xD18, 0xC68));
        REF_STACK(RECT, rect, STACK_OFFS(0xD18, 0xCCC));

        ::SetBkMode(hDC, OPAQUE);
        ::SetBkColor(hDC, RGB(0xFF, 0xFF, 0xFF));

        ppmfc::CString buffer;
        buffer.Format("Money on map: %d", CMapData::Instance->MoneyCount);
        ::TextOut(hDC, rect.left + 10, rect.top + 10, buffer, buffer.GetLength());

        if (ExtConfigs::EnableMultiSelection)
        {
            if (MultiSelection::GetCount())
            {
                int nCount = 0;
                auto pExt = CMapDataExt::GetExtension();
                pExt->InitOreValue();
                MultiSelection::ApplyForEach(
                    [&nCount, pExt](CellData& cell) {
                        nCount += pExt->GetOreValueAt(cell);
                    }
                );

                buffer.Format("Selected money: %d", nCount);
                ::TextOut(hDC, rect.left + 10, rect.top + 30, buffer, buffer.GetLength());
            }
        }
    }
    
    return 0x4750B0;
}

DEFINE_HOOK(4B9F7A, CreateMap_ClearUp_MultiSelection, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    MultiSelection::Clear();

    return 0;
}

DEFINE_HOOK(49D2C0, LoadMap_ClearUp_MultiSelection, 5)
{
    if (!ExtConfigs::EnableMultiSelection)
        return 0;

    MultiSelection::Clear();

    return 0;
}
