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

    ppmfc::CString GetString(const char* pSection, const char* pKey, const char* pDefault = "");

    std::vector<ppmfc::CString> ParseIndicies(const char* pSection, bool bParseIntoValue = false);
    std::map<ppmfc::CString, ppmfc::CString, INISectionEntriesComparator> GetSection(const char* pSection);

private:
    std::vector<INIClass*> data;
};