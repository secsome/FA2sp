#include "ControlHelpers.h"
#include "Translations.h"
#include "STDHelpers.h"
#include "MultimapHelper.h"

#include "../FA2sp.h"

#include <CMapData.h>

namespace ControlHelpers
{
    void ComboBox::LoadHouses(ppmfc::CComboBox& combobox, bool bShowIndex)
    {
        combobox.DeleteAllStrings();

        auto&& entries = Variables::Rules.ParseIndicies("Houses", true);
        CString buffer;
        for (size_t i = 0, sz = entries.size(); i < sz; ++i)
        {
            if (bShowIndex)
                buffer.Format("%u - %s", i, entries[i]);
            else
                buffer = entries[i];
            combobox.SetItemData(combobox.AddString(buffer), i);
        }

        if (CMapData::Instance->IsMultiOnly())
        {
            if (bShowIndex)
            {
                combobox.SetItemData(combobox.AddString("4475 - <Player @ A>"), 4475);
                combobox.SetItemData(combobox.AddString("4476 - <Player @ B>"), 4476);
                combobox.SetItemData(combobox.AddString("4477 - <Player @ C>"), 4477);
                combobox.SetItemData(combobox.AddString("4478 - <Player @ D>"), 4478);
                combobox.SetItemData(combobox.AddString("4479 - <Player @ E>"), 4479);
                combobox.SetItemData(combobox.AddString("4480 - <Player @ F>"), 4480);
                combobox.SetItemData(combobox.AddString("4481 - <Player @ G>"), 4481);
                combobox.SetItemData(combobox.AddString("4482 - <Player @ H>"), 4482);
            }
            else
            {
                combobox.SetItemData(combobox.AddString("<Player @ A>"), 4475);
                combobox.SetItemData(combobox.AddString("<Player @ B>"), 4476);
                combobox.SetItemData(combobox.AddString("<Player @ C>"), 4477);
                combobox.SetItemData(combobox.AddString("<Player @ D>"), 4478);
                combobox.SetItemData(combobox.AddString("<Player @ E>"), 4479);
                combobox.SetItemData(combobox.AddString("<Player @ F>"), 4480);
                combobox.SetItemData(combobox.AddString("<Player @ G>"), 4481);
                combobox.SetItemData(combobox.AddString("<Player @ H>"), 4482);
            }
        }
    }

    void ComboBox::LoadCountries(ppmfc::CComboBox& combobox, bool bShowIndex)
    {
        combobox.DeleteAllStrings();
        auto& doc = CINI::CurrentDocument();
        if (CMapData::Instance->IsMultiOnly())
        {
            ComboBox::LoadHouses(combobox, bShowIndex);
            return;
        }

        auto&& entries = Variables::Rules.ParseIndicies("Countries", true);
        CString buffer;
        for (size_t i = 0, sz = entries.size(); i < sz; ++i)
        {
            if (bShowIndex)
                buffer.Format("%u - %s", i, entries[i]);
            else
                buffer = entries[i];
            combobox.SetItemData(combobox.AddString(buffer), i);
        }
    }

    void ComboBox::LoadGenericList(ppmfc::CComboBox& combobox, const char* pSection, bool bShowRegName, bool bShowIndex, bool bRegNameFirst)
    {
        combobox.DeleteAllStrings();

        auto&& entries = Variables::Rules.ParseIndicies(pSection, true);
        CString buffer;
        for (size_t i = 0, sz = entries.size(); i < sz; ++i)
        {
            if (!bRegNameFirst)
            {
                if (bShowIndex)
                    buffer.Format("%u - %s", i, CMapData::GetUIName(entries[i]));
                else
                    buffer = CMapData::GetUIName(entries[i]);
            }
            else
            {
                if (bShowIndex)
                    buffer.Format("%u - %s", i, entries[i]);
                else
                    buffer = entries[i];
            }
            if (bShowRegName)
                buffer += (" - " + entries[i]);
            combobox.SetItemData(combobox.AddString(buffer), i);
        }

    }
}