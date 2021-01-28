#include <Helpers/Macro.h>

#include "../../FA2sp.h"

// TODO
//DEFINE_HOOK(43CE8D, Miscs_LoadParamToCombobox, 9)
//{
//    GET(CComboBox*, pComboBox, ESI);
//    GET(int, nCode, EAX);
//    while (pComboBox->DeleteString(0) != -1);
//
//    enum { default = 0x43CE96, handled = 0x43D037 };
//
//    if (nCode < 40)
//    {
//
//    }
//    return 0;
//}

DEFINE_HOOK(441910, Miscs_LoadParams_TutorialTexts, 7)
{
    if (ExtConfigs::Stringtables && ExtConfigs::WIP_TutorialTexts)
    {
        GET(CComboBox*, pComboBox, ESI);
        while (pComboBox->DeleteString(0) != CB_ERR);
        for (auto x : FA2sp::WIP_TutorialTextMap)
            pComboBox->AddString((x.first + " : " + x.second).c_str());
        Logger::Debug("%d csf entities added.\n", FA2sp::WIP_TutorialTextMap.size());
        return 0x441A34;
    }
    return 0;
}