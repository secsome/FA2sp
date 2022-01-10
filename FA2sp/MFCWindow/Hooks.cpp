#include <FA2PP.h>
#include <CMyViewFrame.h>
#include <CIsoView.h>

#include <Helpers/Macro.h>

#include "../FA2sp.h"

DEFINE_HOOK(4D2680, CMyViewFrame_OnCreateClient, 5)
{
    if (!ExtConfigs::VerticalLayout)
        return 0;

    GET(CMyViewFrame*, pThis, ECX);
    GET_STACK(LPCREATESTRUCT, lpcs, 0x4);
    GET_STACK(CCreateContext*, pContent, 0x8);

    RECT rect{ 0,0,200,200 };
    SIZE size{ 200,200 };

    BOOL bRes = FALSE;
    if (bRes = pThis->SplitterWnd.FA2CSplitterWnd::CreateStatic(pThis, 1, 2, WS_CHILD | WS_VISIBLE, 0xE900))
    {
        if (bRes = pThis->SplitterWnd.FA2CSplitterWnd::CreateView(0, 0, reinterpret_cast<CRuntimeClass*>(0x598710), size, pContent))
        {
            if (bRes = pThis->SplitterWnd.FA2CSplitterWnd::CreateView(0, 1, reinterpret_cast<CRuntimeClass*>(0x595A88), size, pContent))
            {
                // CMyViewFrame::OnCreateClient(): windows created\n
                pThis->pRightFrame = (CRightFrame*)pThis->SplitterWnd.FA2CSplitterWnd::GetPane(0, 1);
                pThis->pIsoView = (CIsoView*)pThis->pRightFrame->CSplitter.FA2CSplitterWnd::GetPane(0, 0);
                pThis->pIsoView->pParent = pThis;
                pThis->pTileSetBrowserFrame = (CTileSetBrowserFrame*)pThis->pRightFrame->CSplitter.FA2CSplitterWnd::GetPane(0, 1);
                pThis->pViewObjects = (CViewObjects*)pThis->SplitterWnd.FA2CSplitterWnd::GetPane(0, 0);
                pThis->Minimap.CMinimap::CreateEx(0, nullptr, "Minimap", 0, &rect, nullptr, 0);
                pThis->Minimap.CMinimap::Update();
                if (bRes = pThis->StatusBar.FA2CStatusBar::Create(pThis, 0x900, 0x50008200u, 59393))
                {
                    pThis->FA2CFrameWnd::OnCreateClient(lpcs, pContent);
                }
            }
        }
    }
    R->EAX(bRes);

    return 0x4D26BF;
}

DEFINE_HOOK(4D3E50, CRightFrame_OnClientCreate, 5)
{
    if (!ExtConfigs::VerticalLayout)
        return 0;

    GET(CRightFrame*, pThis, ECX);
    GET_STACK(LPCREATESTRUCT, lpcs, 0x4);
    GET_STACK(CCreateContext*, pContent, 0x8);

    SIZE size{ 700,200 };

    BOOL bRes = FALSE;
    if (bRes = pThis->CSplitter.FA2CSplitterWnd::CreateStatic(pThis, 1, 2, WS_CHILD | WS_VISIBLE, 0xE900))
    {
        if (bRes = pThis->CSplitter.FA2CSplitterWnd::CreateView(0, 0, reinterpret_cast<CRuntimeClass*>(0x5942B8), size, pContent))
        {
            size = { 200,200 };
            if (bRes = pThis->CSplitter.FA2CSplitterWnd::CreateView(0, 1, reinterpret_cast<CRuntimeClass*>(0x597378), size, pContent))
            {
                auto const oct = GetSystemMetrics(SM_CXFULLSCREEN) / 8;
                pThis->CSplitter.FA2CSplitterWnd::SetColumnInfo(0, 5 * oct, 20);
                pThis->CSplitter.FA2CSplitterWnd::SetColumnInfo(1, 3 * oct, 10);
                pThis->FA2CFrameWnd::OnCreateClient(lpcs, pContent);
            }
        }
    }

    R->EAX(bRes);

    return 0x4D3E8D;
}