#pragma once

#include <FA2PP.h>

#include <sstream>
#include <algorithm>
#include <vector>

// A class uses STL containers for assistance use

class STDHelpers
{
public:
    static std::vector<CString> SplitString(const char* pSource, char cSplit = 'c')
    {
        std::vector<CString> ret;
        std::istringstream iss(pSource);
        std::string tmp;

        while (std::getline(iss, tmp, cSplit)) {
            ret.push_back(tmp.c_str());
        }

        return ret;
    }
};