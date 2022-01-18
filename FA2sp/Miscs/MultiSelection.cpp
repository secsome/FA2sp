#include "MultiSelection.h"

#include <CFinalSunDlg.h>
#include <CIsoView.h>
#include <Helpers/Macro.h>
#include "../Logger.h"

std::set<MapCoord> MultiSelection::SelectedCoords;
bool MultiSelection::ShiftKeyIsDown = false;
BGRStruct MultiSelection::ColorHolder[0x200];
MapCoord MultiSelection::CurrentCoord;

bool MultiSelection::AddCoord(int X, int Y)
{
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

DEFINE_HOOK(456EFC, CIsoView_OnMouseMove_MultiSelect_ReverseStatus, 6)
{
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
    GET(CIsoView*, pThis, ECX);
    GET_STACK(UINT, nChar, 0x4);

    if (nChar == VK_CONTROL)
        CIsoView::ControlKeyIsDown = false;
    else if (nChar == VK_SHIFT)
        MultiSelection::ShiftKeyIsDown = false;

    R->EAX(pThis->Default());

    return 0x46BC46;
}

DEFINE_HOOK(46EAFA, CIsoView_Draw_TileCurrentCoord, 5)
{
    MultiSelection::CurrentCoord.X = R->EBX();
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
    if (MultiSelection::IsSelected(MultiSelection::CurrentCoord.X, MultiSelection::CurrentCoord.Y))
    {
        GET(BGRStruct*, pColors, ESI);
        GET(int, nCount, ECX);

        static constexpr unsigned char BKColor_R = 0;
        static constexpr unsigned char BKColor_G = 0;
        static constexpr unsigned char BKColor_B = 255;

        for (int i = 0; i < nCount; ++i)
        {
            MultiSelection::ColorHolder[i].R = (pColors[i].R + BKColor_R) / 2;
            MultiSelection::ColorHolder[i].G = (pColors[i].G + BKColor_G) / 2;
            MultiSelection::ColorHolder[i].B = (pColors[i].B + BKColor_B) / 2;

        }

        R->ESI(MultiSelection::ColorHolder);
    }

    return 0;
}

DEFINE_HOOK(433DA0, CFinalSunDlg_Tools_RaiseSingleTile, 5)
{
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

DEFINE_HOOK(4B9F7A, CreateMap_ClearUp_MultiSelection, 5)
{
    MultiSelection::Clear();

    return 0;
}

DEFINE_HOOK(49D2C0, LoadMap_ClearUp_MultiSelection, 5)
{
    MultiSelection::Clear();

    return 0;
}