/*
* NOTICE
* Implement of this class could be really composite and
* hard to understand. Not only to other users, but for me
* as well, so why not just use it as it's easy to call 
* rather than understand how it works, isn't it?
*/

#include "MultimapHelper.h"
#include "STDHelpers.h"

#include <set>

void MultimapHelper::AddINI(INIClass* pINI)
{
    data.push_back(pINI);
}

INIClass* MultimapHelper::GetINIAt(int idx)
{
    return data.at(idx);
}

std::vector<CString> MultimapHelper::ParseIndicies(const char* pSection, bool bParseIntoValue)
{
    std::vector<CString> ret;
    std::map<unsigned int, CString> tmp;
    std::map<CString, unsigned int> tmp2;
    std::map<CString, CString> tmp3; // Value - Key
    std::map<unsigned int, INIClass*> belonging;

    for (auto& pINI : data)
    {
        if (pINI)
        {
            auto& cur = pINI->ParseIndiciesData(pSection);
            for (auto& pair : cur)
            {
                CString value = pINI->GetString(pSection, pair.second, pair.second);
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

std::map<CString, CString, INISectionEntriesComparator> MultimapHelper::GetSection(const char* pSection)
{
    std::map<CString, CString, INISectionEntriesComparator> ret;
    int index = 0;
    CString tmp;
    for (auto& pINI : data)
        if (pINI)
            if (pINI->SectionExists(pSection))
                for (auto& pair : pINI->GetSection(pSection).EntitiesDictionary)
                {
                    if (STDHelpers::IsNullOrEmpty(pair.first) ||
                        STDHelpers::IsNullOrEmpty(pair.second) ||
                        pair.first == "Name")
                    {
                        ++index;
                        continue;
                    }
                    tmp.Format("%d", index++);
                    ret[tmp] = pair.second;
                }
    return ret;
}