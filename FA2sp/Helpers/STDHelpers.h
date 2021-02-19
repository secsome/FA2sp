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
    static std::vector<std::string> SplitString(const char* pSource, char cSplit = ',')
    {
        std::vector<std::string> ret;
        std::istringstream iss(pSource);
        std::string tmp;

        while (std::getline(iss, tmp, cSplit)) {
            ret.push_back(tmp);
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

    static void TrimString(CString& str)
    {
        str.TrimLeft();
        str.TrimRight();
    }

    static void TrimIndex(CString& str)
    {
        TrimString(str);
        int spaceIndex = str.Find(' ');
        if (spaceIndex > 0)
            str = str.Mid(0, spaceIndex);
    }

    static bool Contains(const char* str, const char* query, bool bIgnoreCase = false)
    {
        std::string s = str;
        std::string q = query;
        if (bIgnoreCase)
        {
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            std::transform(q.begin(), q.end(), q.begin(), ::tolower);
        }
        return s.find(q) != std::string::npos;
    }

    // TODO : LCA to optimize the efficiency
    static ppmfc::CString GetAvailableIndex(INIClass& ini)
    {
        CString buffer;
        

        ppmfc::CString ret(buffer);
        return ret;
    }
};