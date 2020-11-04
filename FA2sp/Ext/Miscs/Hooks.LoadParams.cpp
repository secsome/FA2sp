//#include <GlobalVars.h>
#include <Miscs/Miscs.LoadParams.h>
#include <Helpers/Macro.h>

#include "../../Logger.h"

// replace switch here
DEFINE_HOOK(43CE50, Miscs_LoadParamsToCombobox, 7)
{
    GET_STACK(CComboBox*, pComboBox, -0x8);
    GET_STACK(int, nParamCode, -0x4);
    
    //Logger::Debug("%08X %08X\n", pComboBox, pComboBox->m_hWnd);

    return 
        true ? 0 : 
        0x43D058;
}

auto AddString = [](HWND hComboBox, const char* lpString)
{
    SendMessage(hComboBox, CB_ADDSTRING, NULL, (LPARAM)lpString);
};

DEFINE_HOOK(43CFB4, Miscs_LoadParams_CrateTypes, 6)
{
    GET(HWND, hComboBox, EDX);
    while (SendMessage(hComboBox, CB_GETCOUNT, 0, NULL) > 0)
        SendMessage(hComboBox, CB_DELETESTRING, 0, 0);
    AddString(hComboBox, "0 - Money");
    AddString(hComboBox, "1 - Unit");
    AddString(hComboBox, "2 - HealBase");
    AddString(hComboBox, "3 - Cloak");
    AddString(hComboBox, "4 - Explosion");
    AddString(hComboBox, "5 - Napalm");
    AddString(hComboBox, "6 - Squad (not working)");
    AddString(hComboBox, "7 - Darkness");
    AddString(hComboBox, "8 - Reveal");
    AddString(hComboBox, "9 - Armor");
    AddString(hComboBox, "10 - Speed");
    AddString(hComboBox, "11 - Firepower");
    AddString(hComboBox, "12 - ICBM");
    AddString(hComboBox, "13 - Invulnerability (not working)");
    AddString(hComboBox, "14 - Veteran");
    AddString(hComboBox, "15 - IonStorm");
    AddString(hComboBox, "16 - Gas");
    AddString(hComboBox, "17 - Tiberium");
    AddString(hComboBox, "18 - Pod (not working)");
    return 0x43D037;
}

DEFINE_HOOK(43CFE4, Miscs_LoadParams_SpeechBubble, 6) 
{
    GET(HWND, hComboBox, ECX);
    while (SendMessage(hComboBox, CB_GETCOUNT, 0, NULL) > 0)
        SendMessage(hComboBox, CB_DELETESTRING, 0, 0);
    AddString(hComboBox, "0 - None");
    AddString(hComboBox, "1 - Asterisk(*)");
    AddString(hComboBox, "2 - Question mark(?)");
    AddString(hComboBox, "3 - Exclamation mark(!)");
    return 0x43D037;
}

#undef AddString