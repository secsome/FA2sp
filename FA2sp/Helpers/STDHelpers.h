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
    static std::vector<ppmfc::CString> SplitString(const ppmfc::CString& pSource, const char* pSplit = ",");
    static std::vector<ppmfc::CString> SplitString(const ppmfc::CString& pSource, size_t nth, const char* pSplit = ",");
    static int ParseToInt(const char* pSource, int nDefault = 0);
    static bool IsNullOrEmpty(const char* pSource);
    static bool IsNullOrWhitespace(const char* pSource);
    static bool IsNoneOrEmpty(const char* pSource);
    static void TrimString(ppmfc::CString& str);
    static void TrimIndex(ppmfc::CString& str);
    static bool Contains(ppmfc::CString pStr, ppmfc::CString pQuery, bool bIgnoreCase = false);
    static ppmfc::CString GetComboBoxText(const ppmfc::CComboBox& cbb);

};