#pragma once

#include <FA2PP.h>

namespace ControlHelpers
{
class ComboBox
{
public:
    static void LoadHouses(ppmfc::CComboBox& combobox, bool bShowIndex = false);
    static void LoadCountries(ppmfc::CComboBox& combobox, bool bShowIndex = false);
    static void LoadGenericList(ppmfc::CComboBox& combobox, const char* pSection, bool bShowRegName = false, bool bShowIndex = false, bool bRegNameFirst = false);
};


}