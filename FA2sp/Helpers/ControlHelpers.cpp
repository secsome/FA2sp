#include "ControlHelpers.h"
#include "Translations.h"
#include "STDHelpers.h"
#include "MultimapHelper.h"

#include <GlobalVars.h>

namespace ControlHelpers
{
    void ComboBox::Clear(CComboBox& combobox)
    {
        while (combobox.DeleteString(0) != -1);
    }

    void ComboBox::LoadHouses(CComboBox& combobox, bool bShowIndex)
    {
        ComboBox::Clear(combobox);

        auto& doc = GlobalVars::INIFiles::CurrentDocument();
        MultimapHelper mmh;
        mmh.AddINI(&doc);

        auto& entries = mmh.ParseIndicies("Houses", true);
        CString buffer;
        for (size_t i = 0, sz = entries.size(); i < sz; ++i)
        {
            if (bShowIndex)
                buffer.Format("%u - %s", i, entries[i]);
            else
                buffer = entries[i];
            combobox.SetItemData(combobox.AddString(buffer), i);
        }

        bool bMultiOnly = doc.GetBool("Basic", "MultiplayerOnly");
        if (bMultiOnly)
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

    void ComboBox::LoadCountries(CComboBox& combobox, bool bShowIndex)
    {
        ComboBox::Clear(combobox);
        auto& doc = GlobalVars::INIFiles::CurrentDocument();
        bool bMultiOnly = doc.GetBool("Basic", "MultiplayerOnly");
        if (bMultiOnly)
        {
            ComboBox::LoadHouses(combobox, bShowIndex);
            return;
        }

        MultimapHelper mmh;
        mmh.AddINI(&GlobalVars::INIFiles::Rules());
        mmh.AddINI(&GlobalVars::INIFiles::CurrentDocument());

        auto& entries = mmh.ParseIndicies("Countries", true);
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

    void ComboBox::LoadGenericList(CComboBox& combobox, const char* pSection, bool bShowRegName, bool bShowIndex)
    {
        ComboBox::Clear(combobox);

        MultimapHelper mmh;
        mmh.AddINI(&GlobalVars::INIFiles::Rules());
        mmh.AddINI(&GlobalVars::INIFiles::CurrentDocument());

        auto& entries = mmh.ParseIndicies(pSection, true);
        CString buffer;
        for (size_t i = 0, sz = entries.size(); i < sz; ++i)
        {
            if (bShowIndex)
                buffer.Format("%u - %s", i, CSFQuery::GetUIName(entries[i]));
            else
                buffer = CSFQuery::GetUIName(entries[i]);
            if (bShowRegName)
                buffer += (" - " + entries[i]);
            combobox.SetItemData(combobox.AddString(buffer), i);
        }

    }
}