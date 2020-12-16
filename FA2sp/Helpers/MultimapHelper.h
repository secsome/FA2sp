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
    std::map<CString, CString, INISectionEntriesComparator> GetSection(const char* pSection);

private:
    std::vector<INIClass*> data;
};