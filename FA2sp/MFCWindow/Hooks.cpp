#include <FA2PP.h>
#include <CMyViewFrame.h>
#include <CTileSetBrowserFrame.h>
#include <CIsoView.h>

#include <Helpers/Macro.h>

#include "../FA2sp.h"

DEFINE_HOOK(4D2680, CMyViewFrame_OnCreateClient, 5)
{
    if (!ExtConfigs::VerticalLayout)
        return 0;

    GET(CMyViewFrame*, pThis, ECX);
    GET_STACK(LPCREATESTRUCT, lpcs, 0x4);
    GET_STACK(ppmfc::CCreateContext*, pContent, 0x8);

    RECT rect{ 0,0,200,200 };
    SIZE size{ 200,200 };

    BOOL bRes = FALSE;
    if (bRes = pThis->SplitterWnd.CreateStatic(pThis, 1, 2, WS_CHILD | WS_VISIBLE))
    {
        if (bRes = pThis->SplitterWnd.CreateView(0, 0, reinterpret_cast<ppmfc::CRuntimeClass*>(0x598710), size, pContent))
        {
            if (bRes = pThis->SplitterWnd.CreateView(0, 1, &CRightFrame::RuntimeClass, size, pContent))
            {
                // CMyViewFrame::OnCreateClient(): windows created\n
                pThis->pRightFrame = (CRightFrame*)pThis->SplitterWnd.GetPane(0, 1);
                pThis->pIsoView = (CIsoView*)pThis->pRightFrame->CSplitter.GetPane(0, 0);
                pThis->pIsoView->pParent = pThis;
                pThis->pTileSetBrowserFrame = (CTileSetBrowserFrame*)pThis->pRightFrame->CSplitter.GetPane(0, 1);
                pThis->pViewObjects = (CViewObjects*)pThis->SplitterWnd.GetPane(0, 0);
                pThis->Minimap.CreateEx(0, nullptr, "Minimap", 0, rect, nullptr, 0);
                pThis->Minimap.Update();
                if (bRes = pThis->StatusBar.CreateEx(pThis, 0x900))
                {
                    pThis->OnCreateClient(lpcs, pContent);
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
    GET_STACK(ppmfc::CCreateContext*, pContent, 0x8);

    SIZE size{ 700,200 };

    BOOL bRes = FALSE;
    if (bRes = pThis->CSplitter.CreateStatic(pThis, 1, 2, WS_CHILD | WS_VISIBLE))
    {
        if (bRes = pThis->CSplitter.CreateView(0, 0, &CIsoView::RuntimeClass, size, pContent))
        {
            size = { 200,200 };
            if (bRes = pThis->CSplitter.CreateView(0, 1, &CTileSetBrowserFrame::RuntimeClass, size, pContent))
            {
                auto const oct = GetSystemMetrics(SM_CXFULLSCREEN) / 8;
                pThis->CSplitter.SetColumnInfo(0, 5 * oct, 20);
                pThis->CSplitter.SetColumnInfo(1, 3 * oct, 10);
                pThis->OnCreateClient(lpcs, pContent);
            }
        }
    }

    R->EAX(bRes);

    return 0x4D3E8D;
}