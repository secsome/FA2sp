#include "STDHelpers.h"

std::vector<ppmfc::CString> STDHelpers::SplitString(const ppmfc::CString& pSource, const char* pSplit)
{
    std::vector<ppmfc::CString> ret;
    if (pSource.GetLength() == 0)
        return ret;

    int nIdx = 0;
    while (true)
    {
        int nPos = pSource.Find(pSplit, nIdx);
        if (nPos == -1)
            break;

        ret.push_back(pSource.Mid(nIdx, nPos - nIdx));
        nIdx = nPos + 1;
    }
    ret.push_back(pSource.Mid(nIdx));
    return ret;
}

std::vector<ppmfc::CString> STDHelpers::SplitString(const ppmfc::CString& pSource, size_t nth, const char* pSplit)
{
    std::vector<ppmfc::CString> ret;
    if (pSource.GetLength() == 0)
        return ret;

    size_t i = 0;

    int nIdx = 0;
    while (true)
    {
        int nPos = pSource.Find(pSplit, nIdx);
        if (nPos == -1)
            break;

        ret.push_back(pSource.Mid(nIdx, nPos - nIdx));
        nIdx = nPos + 1;
        if (++i > nth)
            return ret;
    }
    if (nIdx != pSource.GetLength() - 1)
    {
        ++i;
        ret.push_back(pSource.Mid(nIdx));
    }
    return ret;
}

int STDHelpers::ParseToInt(const char* pSource, int nDefault)
{
    int ret;
    if (sscanf_s(pSource, "%d", &ret) != 1)
        return nDefault;
    return ret;
}

bool STDHelpers::IsNullOrEmpty(const char* pSource)
{
    return pSource == nullptr || strlen(pSource) == 0;
}

bool STDHelpers::IsNullOrWhitespace(const char* pSource)
{
    if (pSource == nullptr)
        return true;

    auto p = pSource;
    auto q = pSource + strlen(pSource);
    while (p != q)
    {
        if (*p != '\0' && *p != ' ')
            return false;
        ++p;
    }

    return true;
}

bool STDHelpers::IsNoneOrEmpty(const char* pSource)
{
    int len = strlen(pSource);
    if (len == 0)  return true;
    for (int i = 0; i < len; ++i)
        if (pSource[i] != ' ' && pSource[i] != '\0')  return false;
    return
        strcmp(pSource, "none") != 0 &&
        strcmp(pSource, "<none>") != 0;
}

void STDHelpers::TrimString(ppmfc::CString& str)
{
    str.TrimLeft();
    str.TrimRight();
}

void STDHelpers::TrimIndex(ppmfc::CString& str)
{
    TrimString(str);
    int spaceIndex = str.Find(' ');
    if (spaceIndex > 0)
        str = str.Mid(0, spaceIndex);
}

bool STDHelpers::Contains(ppmfc::CString pStr, ppmfc::CString pQuery, bool bIgnoreCase)
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

ppmfc::CString STDHelpers::GetComboBoxText(const ppmfc::CComboBox& cbb)
{
    int nCurSel = cbb.GetCurSel();
    ppmfc::CString ret;

    if (nCurSel == CB_ERR)
        cbb.GetWindowText(ret);
    else
        cbb.GetLBText(nCurSel, ret);

    return ret;
}