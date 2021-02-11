#pragma once

#include <CINI.h>

#include <vector>
#include <map>

class MultimapHelper
{
public:
    MultimapHelper() = default;

    void AddINI(INIClass* pINI);

    INIClass* GetINIAt(int idx);

    CString GetString(const char* pSection, const char* pKey, const char* pDefault = "");

    std::vector<CString> ParseIndicies(const char* pSection, bool bParseIntoValue = false);
    std::map<CString, CString, INISectionEntriesComparator> GetSection(const char* pSection);

private:
    std::vector<INIClass*> data;
};