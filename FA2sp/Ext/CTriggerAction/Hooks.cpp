#include "Body.h"

int CTriggerActionExt::nCurrentParamCode;

DEFINE_HOOK(4F8617, CTriggerAction_OnLBParamsSelChanged_SetCurrentParamCode, 7)
{
    GET_STACK(char*, pBuffer, STACK_OFFS(0xC4, 0x88));

    CTriggerActionExt::nCurrentParamCode = atoi(pBuffer);

    return 0;
}


DEFINE_HOOK(4F863A, CTriggerAction_OnLBParamsSelChanged_ReadParamValue, 5)
{
    if (CTriggerActionExt::nCurrentParamCode == 30) // Float
    {
        GET(ppmfc::CString*, pParamValue, EAX);

        unsigned int nValue;
        if (sscanf_s(*pParamValue, "%u", &nValue) == 1)
            pParamValue->Format("%f", *(float*)&nValue);
    }

    return 0;
}

DEFINE_HOOK(4F8BC4, CTriggerAction_OnCBParamValueEditChanged_WriteParamValue, 6)
{
    if (CTriggerActionExt::nCurrentParamCode == 30) // Float
    {
        REF_STACK(ppmfc::CString, pParamValue, STACK_OFFS(0xB4, 0xA0));

        float fValue;
        if (sscanf_s(pParamValue, "%f", &fValue) == 1)
            pParamValue.Format("%010u", *(unsigned int*)&fValue);
    }

    return 0;
}