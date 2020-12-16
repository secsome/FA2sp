#pragma once

#include <FA2PP.h>

#include <sstream>
#include <algorithm>
#include <vector>

// A class uses STL containers for assistance use

class STDHelpers
{
public:
    static std::vector<CString> SplitString(const char* pSource, char cSplit = ',')
    {
        std::vector<CString> ret;
        std::istringstream iss(pSource);
        std::string tmp;

        while (std::getline(iss, tmp, cSplit)) {
            ret.push_back(tmp.c_str());
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
        return true;
    }
};