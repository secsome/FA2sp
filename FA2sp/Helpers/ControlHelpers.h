#pragma once

#include <FA2PP.h>

namespace ControlHelpers
{
class ComboBox
{
public:
    static void Clear(CComboBox& combobox);
    static void LoadHouses(CComboBox& combobox, bool bShowIndex = false);
    static void LoadCountries(CComboBox& combobox, bool bShowIndex = false);
    static void LoadGenericList(CComboBox& combobox, const char* pSection, bool bShowRegName = false, bool bShowIndex = false);
};


}