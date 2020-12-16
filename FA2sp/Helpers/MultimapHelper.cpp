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