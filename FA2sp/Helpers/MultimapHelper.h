#pragma once

#include <CINI.h>

#include <vector>
#include <map>

class MultimapHelper
{
public:
    MultimapHelper() = default;
    MultimapHelper(std::initializer_list<CINI*> list);

    void AddINI(CINI* pINI);

    CINI* GetINIAt(int idx);

    ppmfc::CString* TryGetString(ppmfc::CString pSection, ppmfc::CString pKey);
    int GetInteger(ppmfc::CString pSection, ppmfc::CString pKey, int nDefault = 0);
    float GetSingle(ppmfc::CString pSection, ppmfc::CString pKey, float nDefault = 0.0f);
    ppmfc::CString GetString(ppmfc::CString pSection, ppmfc::CString pKey, ppmfc::CString pDefault = "");
    bool GetBool(ppmfc::CString pSection, ppmfc::CString pKey, bool nDefault = false);

    std::vector<ppmfc::CString> ParseIndicies(ppmfc::CString pSection, bool bParseIntoValue = false);
    std::map<ppmfc::CString, ppmfc::CString, INISectionEntriesComparator> GetSection(ppmfc::CString pSection);

private:
    std::vector<CINI*> data;
};