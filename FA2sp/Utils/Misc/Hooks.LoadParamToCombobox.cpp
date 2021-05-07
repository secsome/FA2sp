#include <Helpers/Macro.h>
#include <CINI.h>

#include <map>

#include "../../FA2sp.h"
#include "../../Helpers/STDHelpers.h"

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

DEFINE_HOOK(43D037, Miscs_LoadParams_AdjustComboboxDropdownWidth, C)
{
    if (ExtConfigs::AdjustDropdownWidth)
    {
        GET_STACK(CComboBox*, pComboBox, STACK_OFFS(0x18, -0x4));

        int nMaxWidth = 120;
        for (int i = 0; i < pComboBox->GetCount(); ++i)
            nMaxWidth = std::max(nMaxWidth, pComboBox->GetLBTextLen(i) * ExtConfigs::AdjustDropdownWidth_Factor);
        pComboBox->SetDroppedWidth(nMaxWidth);
    }

    return 0;
}

DEFINE_HOOK(441910, Miscs_LoadParams_TutorialTexts, 7)
{
    GET_STACK(CComboBox*, pComboBox, 0x4);
    if (ExtConfigs::TutorialTexts_Hide)
    {
        while (pComboBox->DeleteString(0) != CB_ERR);
        return 0x441A34;
    }
    if (ExtConfigs::Stringtables && ExtConfigs::TutorialTexts_Fix)
    {   
        while (pComboBox->DeleteString(0) != CB_ERR);
        for (auto x : FA2sp::TutorialTextsMap)
            pComboBox->AddString((x.first + " : " + x.second).c_str());
        Logger::Debug("%d csf entities added.\n", FA2sp::TutorialTextsMap.size());
        return 0x441A34;
    }
    return 0;
}

DEFINE_HOOK(441A40, Miscs_LoadParams_Triggers, 6)
{
    GET_STACK(CComboBox*, pComboBox, 0x4);
    if (ExtConfigs::SortByTriggerName)
    {
        // Param value combobox
        if (pComboBox->GetDlgCtrlID() == 1402/* && pComboBox->GetParent()->GetDlgCtrlID() == 252*/)
        {
            while (pComboBox->DeleteString(0) != CB_ERR);

            std::map<ppmfc::CString, ppmfc::CString> collector;

            auto const pINI = INIClass::GetMapDocument(true);
            if (auto const pSection = pINI->GetSection("Triggers"))
            {
                for (auto pair : pSection->EntitiesDictionary)
                {
                    ppmfc::CString key(STDHelpers::SplitString(pair.second)[2].c_str());
                    ppmfc::CString buffer(pair.first);
                    buffer += " (";
                    buffer += key;
                    buffer += ")";
                    
                    collector.insert(std::make_pair(key, buffer));
                }
            }

            for (auto pair : collector)
                pComboBox->AddString(pair.second);

            collector.clear();

            return 0x441DF6;
        }
    }
    return 0;
}
