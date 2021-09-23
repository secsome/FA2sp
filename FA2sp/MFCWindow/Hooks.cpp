#include <FA2PP.h>
#include <CMyViewFrame.h>
#include <CIsoView.h>

#include <Helpers/Macro.h>

DEFINE_HOOK(4D2680, CMyViewFrame_OnCreateClient, 5)
{
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
                pThis->pTileSetBrowserView = (CTileSetBrowserView*)pThis->pRightFrame->CSplitter.FA2CSplitterWnd::GetPane(1, 0);
                pThis->pObjectBrowserControl = (ObjectBrowserControl*)pThis->SplitterWnd.FA2CSplitterWnd::GetPane(0, 0);
                pThis->Minimap.CWndView::CreateEx(0, nullptr, "Minimap", 0, &rect, nullptr, 0);
                pThis->Minimap.CWndView::Update();
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