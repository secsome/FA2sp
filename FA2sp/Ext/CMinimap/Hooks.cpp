#include <Helpers/Macro.h>

#include "Body.h"

#include <CMapData.h>
#include <CFinalSunDlg.h>
#include <CIsoView.h>

//DEFINE_HOOK(4D1B50, CMinimap_OnDraw, 7)
//{
//    GET(CMinimap*, pThis, ECX);
//    GET_STACK(CDC*, pDC, 0x4);
//
//    BITMAPINFO bmi;
//    if (auto const pBuffer = CMapData::Instance->GetMapPreview(&bmi))
//    {
//        ::StretchDIBits(pDC->m_hDC, 0, 0, CMapData::Instance->Size.Width, CMapData::Instance->Size.Height,
//            0, 0, 2 * CMapData::Instance->Size.Width, CMapData::Instance->Size.Height,
//            pBuffer, &bmi, DIB_RGB_COLORS, SRCCOPY);
//
//
//    }
//
//    return 0x4D1CE0;
//}
//
//DEFINE_HOOK(4D1E0F, CMinimap_UpdateDialog_Size, 8)
//{
//    R->ECX(R->Stack32(STACK_OFFS(0x2C, 0x10)));
//    R->EAX(R->EAX() + R->EDI());
//    return 0x4D1E17;
//}