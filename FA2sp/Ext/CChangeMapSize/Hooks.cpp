#include "Body.h"

#include <Helpers/Macro.h>

#include <CMapData.h>
#include <CFinalSunDlg.h>
#include <CMyViewFrame.h>
#include <CIsoView.h>
#include <CMinimap.h>

DEFINE_HOOK(41B0E0, CChangeMapSize_DoDataExchange, 6)
{
    GET(CChangeMapSize*, pThis, ECX);
    GET_STACK(ppmfc::CDataExchange*, pDX, 0x4);

    ppmfc::DDX_Text(pDX, 1036, pThis->INT_Left);
    ppmfc::DDX_Text(pDX, 1037, pThis->INT_Top);
    ppmfc::DDX_Text(pDX, 1373, pThis->INT_Width);
    ppmfc::DDX_Text(pDX, 1374, pThis->INT_Height);
    
    return 0x41B148;
}

DEFINE_HOOK(499D56, CMapD_OnBNChangeMapSizeClicked_ValidCheck, 7)
{
    GET(CMapD*, pThis, ESI);
    REF_STACK(CChangeMapSize, cms, STACK_OFFS(0xB0, 0xAC));

    if (cms.INT_Width < 1 || cms.INT_Width > 256 || cms.INT_Height < 1 || cms.INT_Height > 256)
    {
        R->ESI<ppmfc::CDialog*>()->MessageBox("Width and Height must be between 1 and 256!");   
    }
    else
    {
        CMapData::Instance->ResizeMap(
            cms.INT_Left,
            cms.INT_Top,
            cms.INT_Width,
            cms.INT_Height
        );
        CFinalSunDlg::Instance->MyViewFrame.pIsoView->RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
        CFinalSunDlg::Instance->MyViewFrame.Minimap.Update();
        pThis->CString_Width.Format("%d", cms.INT_Width);
        pThis->CString_Height.Format("%d", cms.INT_Height);
        pThis->UpdateData(FALSE);
    }

    return 0x499E30;
}