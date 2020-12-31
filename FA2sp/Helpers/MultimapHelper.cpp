#include "MultimapHelper.h"
#include "STDHelpers.h"

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
    std::map<unsigned int, INIClass*> belonging;

    for (auto& pINI : data)
    {
        if (pINI)
        {
            auto& cur = pINI->ParseIndiciesData(pSection);
            for (auto& pair : cur)
            {
                auto& itr = tmp2.find(pair.second);
                if (itr == tmp2.end())
                {
                    belonging[tmp2.size()] = pINI;
                    tmp2[pair.second] = tmp2.size();
                }
            }
        }
    }
    for (auto& pair : tmp2)
        tmp[pair.second] = pair.first;
    ret.resize(tmp.size());
    size_t idx = 0;
    for (auto& x : tmp)
        ret[idx++] = x.second;

    if (bParseIntoValue)
        for (size_t i = 0, sz = ret.size(); i < sz; ++i)
            ret[i] = belonging[i]->GetString(pSection, ret[i], ret[i]);

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