#pragma once

#include <CINI.h>

#include <vector>
#include <map>

class MultimapHelper
{
public:
    MultimapHelper() = default;
    MultimapHelper(std::initializer_list<INIClass*> list);

    void AddINI(INIClass* pINI);

    INIClass* GetINIAt(int idx);

    ppmfc::CString* TryGetString(ppmfc::CString pSection, ppmfc::CString pKey);
    int GetInteger(ppmfc::CString pSection, ppmfc::CString pKey, int nDefault = 0);
    ppmfc::CString GetString(ppmfc::CString pSection, ppmfc::CString pKey, ppmfc::CString pDefault = "");
    bool GetBool(ppmfc::CString pSection, ppmfc::CString pKey, bool nDefault = false);

    std::vector<ppmfc::CString> ParseIndicies(ppmfc::CString pSection, bool bParseIntoValue = false);
    std::map<ppmfc::CString, ppmfc::CString, INISectionEntriesComparator> GetSection(ppmfc::CString pSection);

private:
    std::vector<INIClass*> data;
};