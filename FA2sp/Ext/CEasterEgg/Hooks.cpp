#include <CEasterEgg.h>

#include <Helpers/Macro.h>

bool CGamePanel_IsAlreadyOver(CGamePanel* pPanel)
{
    for (int i = 0; i < 3; ++i)
    {
        if (pPanel->GetBlock(i, 0) == pPanel->GetBlock(i, 1) &&
            pPanel->GetBlock(i, 0) == pPanel->GetBlock(i, 2) &&
            pPanel->GetBlock(i, 0) != CGamePanel::BlockType::None)
            return true;

        if (pPanel->GetBlock(0, i) == pPanel->GetBlock(1, i) &&
            pPanel->GetBlock(0, i) == pPanel->GetBlock(2, i) &&
            pPanel->GetBlock(0, i) != CGamePanel::BlockType::None)
            return true;
    }

    if (pPanel->GetBlock(0, 0) == pPanel->GetBlock(1, 1) &&
        pPanel->GetBlock(0, 0) == pPanel->GetBlock(2, 2) &&
        pPanel->GetBlock(0, 0) != CGamePanel::BlockType::None)
        return true;

    if (pPanel->GetBlock(2, 0) == pPanel->GetBlock(1, 1) &&
        pPanel->GetBlock(2, 0) == pPanel->GetBlock(0, 2) &&
        pPanel->GetBlock(2, 0) != CGamePanel::BlockType::None)
        return true;

    return false;
}

DEFINE_HOOK(41E8F0, CGamePanel_OnLButtonDown, 7)
{
    GET(CGamePanel*, pThis, ECX);
    GET_STACK(UINT, nFlags, 0x4);
    REF_STACK(const CPoint, point, 0x8);

    if (!CGamePanel_IsAlreadyOver(pThis))
    {
        RECT rect;
        ::GetClientRect(pThis->m_hWnd, &rect);
        auto& state = pThis->GetBlock(point.x / (rect.right / 3), point.y / (rect.bottom / 3));
        if (state == CGamePanel::BlockType::None)
        {
            state = CGamePanel::BlockType::Player;
            ::RedrawWindow(pThis->m_hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            pThis->CanPlayerPlace = false;
            pThis->AI();
        }
    }
    ::RedrawWindow(pThis->m_hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);

    return 0x41E99D;
}

DEFINE_HOOK(41E9A0, CGamePanel_AI, 7)
{
    GET(CGamePanel*, pThis, ECX);

    return 0;
}