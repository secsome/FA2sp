/*
* NOTICE
* Implement of this class could be really composite and
* hard to understand. Not only to other users, but for me
* as well, so why not just use it as it's easy to call 
* rather than understand how it works, isn't it?
* 
* UPDATE ON 3/31/2021
* "I cannot understand this one either now." - secsome
*/

#include "MultimapHelper.h"
#include "STDHelpers.h"

#include <set>

MultimapHelper::MultimapHelper(std::initializer_list<CINI*> list)
{
    for (auto pINI : list)
        data.push_back(pINI);
}

void MultimapHelper::AddINI(CINI* pINI)
{
    data.push_back(pINI);
}

CINI* MultimapHelper::GetINIAt(int idx)
{
    return data.at(idx);
}

ppmfc::CString* MultimapHelper::TryGetString(ppmfc::CString pSection, ppmfc::CString pKey)
{
    for (auto ritr = data.rbegin(); ritr != data.rend(); ++ritr)
    {
        if (auto pRet = (*ritr)->TryGetString(pSection, pKey))
            if (!pRet->IsEmpty())
                return pRet;
    }
    return nullptr;
}

ppmfc::CString MultimapHelper::GetString(ppmfc::CString pSection, ppmfc::CString pKey, ppmfc::CString pDefault)
{
    auto const pResult = TryGetString(pSection, pKey);
    return pResult ? *pResult : pDefault;
}

int MultimapHelper::GetInteger(ppmfc::CString pSection, ppmfc::CString pKey, int nDefault) {
    ppmfc::CString& pStr = this->GetString(pSection, pKey, "");
    int ret = 0;
    if (sscanf_s(pStr, "%d", &ret) == 1)
        return ret;
    return nDefault;
}

bool MultimapHelper::GetBool(ppmfc::CString pSection, ppmfc::CString pKey, bool nDefault) {
    ppmfc::CString& pStr = this->GetString(pSection, pKey, "");
    switch (toupper(static_cast<unsigned char>(*pStr)))
    {
    case '1':
    case 'T':
    case 'Y':
        return true;
    case '0':
    case 'F':
    case 'N':
        return false;
    default:
        return nDefault;
    }
}

std::vector<ppmfc::CString> MultimapHelper::ParseIndicies(ppmfc::CString pSection, bool bParseIntoValue)
{
    std::vector<ppmfc::CString> ret;
    std::map<unsigned int, ppmfc::CString> tmp;
    std::map<ppmfc::CString, unsigned int> tmp2;
    std::map<ppmfc::CString, ppmfc::CString> tmp3; // Value - Key
    std::map<unsigned int, CINI*> belonging;

    for (auto& pINI : data)
    {
        if (pINI)
        {
            auto& cur = pINI->ParseIndiciesData(pSection);
            for (auto& pair : cur)
            {
                ppmfc::CString value = pINI->GetString(pSection, pair.second, pair.second);
                auto& unitr = tmp2.find(value);
                if (unitr == tmp2.end())
                {
                    belonging[tmp2.size()] = pINI;
                    tmp2[value] = tmp2.size();
                }
                else
                {
                    belonging[unitr->second] = pINI;
                }
                tmp3[value] = pair.second;
            }
        }
    }
    
    for (auto& pair : tmp2)
        tmp[pair.second] = pair.first;

    ret.resize(tmp.size());
    size_t idx = 0;
    for (auto& x : tmp)
        ret[idx++] = x.second;

    if (!bParseIntoValue)
        for (size_t i = 0, sz = ret.size(); i < sz; ++i)
            ret[i] = tmp3[ret[i]];

    return ret;
}

std::map<ppmfc::CString, ppmfc::CString, INISectionEntriesComparator> MultimapHelper::GetSection(ppmfc::CString pSection)
{
    std::map<ppmfc::CString, ppmfc::CString, INISectionEntriesComparator> ret;
    int index = 0;
    ppmfc::CString tmp;
    for (auto& pINI : data)
        if (pINI)
            if (auto section = pINI->GetSection(pSection))
            {
                for (auto& pair : section->GetEntities())
                {
                    if (STDHelpers::IsNoneOrEmpty(pair.first) ||
                        STDHelpers::IsNoneOrEmpty(pair.second) ||
                        pair.first == "Name")
                    {
                        ++index;
                        continue;
                    }
                    tmp.Format("%d", index++);
                    ret[tmp] = pair.second;
                }
            }         
    return ret;
}