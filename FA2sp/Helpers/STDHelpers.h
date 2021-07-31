#pragma once

#include <FA2PP.h>

#include <sstream>
#include <algorithm>
#include <vector>

#include <MFC/ppmfc_cstring.h>

#include <CINI.h>

// A class uses STL containers for assistance use

class STDHelpers
{
public:
    static std::vector<ppmfc::CString> SplitString(const char* pSource, const char* pSplit = ",")
    {
        std::vector<ppmfc::CString> ret;

        char* tokenPtr = strtok(const_cast<char*>(pSource), pSplit);
        while (tokenPtr != nullptr) {
            ret.push_back(tokenPtr);
            tokenPtr = strtok(nullptr, pSplit);
        }

        return ret;
    }

    static int ParseToInt(const char* pSource, int nDefault = 0)
    {
        int ret;
        if (sscanf_s(pSource, "%d", &ret) != 1)
            return nDefault;
        return ret;
    }

    static bool IsNullOrEmpty(const char* pSource)
    {
        int len = strlen(pSource);
        if (len == 0)  return true;
        for (int i = 0; i < len; ++i)
            if (pSource[i] != ' ' && pSource[i] != '\0')  return false;
        return 
            strcmp(pSource, "none") != 0 &&
            strcmp(pSource, "<none>") != 0;
    }

    static void TrimString(ppmfc::CString& str)
    {
        str.TrimLeft();
        str.TrimRight();
    }

    static void TrimIndex(ppmfc::CString& str)
    {
        TrimString(str);
        int spaceIndex = str.Find(' ');
        if (spaceIndex > 0)
            str = str.Mid(0, spaceIndex);
    }

    static bool Contains(ppmfc::CString pStr, ppmfc::CString pQuery, bool bIgnoreCase = false)
    {
        if (bIgnoreCase)
        {
            ppmfc::CString s = pStr;
            ppmfc::CString q = pQuery;
            s.MakeLower();
            q.MakeLower();
            return s.Find(q) != -1;
        }
        else
            return pStr.Find(pQuery) != -1;
    }
};