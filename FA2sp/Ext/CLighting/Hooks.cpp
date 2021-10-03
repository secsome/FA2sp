#include "Body.h"

#include <Helpers/Macro.h>
#include <CINI.h>
#include <CFinalSunDlg.h>

DEFINE_HOOK(432577, CFinalSunDlg_UpdateDialog_Translate_CLighting,5)
{
    GET(CFinalSunDlg*, pThis, ESI);

    if (pThis->Lighting.m_hWnd)
        reinterpret_cast<CLightingExt*>(&pThis->Lighting)->Translate();

    return 0;
}

DEFINE_HOOK(478428, CLighting_OnInitDialog, 5)
{
    GET(CLightingExt*, pThis, ESI);

    pThis->Translate();

    return 0x478439;
}

DEFINE_HOOK(478407, CLighting_UpdateDialog, 7)
{
    GET(CLighting*, pThis, ESI);

    pThis->SetDlgItemText(1068, CINI::CurrentDocument->GetString("Lighting", "DominatorAmbient", "0.850000"));
    pThis->SetDlgItemText(1069, CINI::CurrentDocument->GetString("Lighting", "DominatorGreen", "0.300000"));
    pThis->SetDlgItemText(1070, CINI::CurrentDocument->GetString("Lighting", "DominatorRed", "0.200000"));
    pThis->SetDlgItemText(1071, CINI::CurrentDocument->GetString("Lighting", "DominatorBlue", "0.000000"));
    pThis->SetDlgItemText(1072, CINI::CurrentDocument->GetString("Lighting", "DominatorLevel", "1.000000"));

    pThis->SetDlgItemText(1073, CINI::CurrentDocument->GetString("Lighting", "Ground", "0.080000"));
    pThis->SetDlgItemText(1074, CINI::CurrentDocument->GetString("Lighting", "IonGround", "0.000000"));
    pThis->SetDlgItemText(1075, CINI::CurrentDocument->GetString("Lighting", "DominatorGround", "0.000000"));

    pThis->SetDlgItemText(1076, CINI::CurrentDocument->GetString("Lighting", "NukeAmbientChangeRate", "1.500000"));
    pThis->SetDlgItemText(1077, CINI::CurrentDocument->GetString("Lighting", "DominatorAmbientChangeRate", "0.000000"));

    return 0;
}