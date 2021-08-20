#include <Helpers/Macro.h>

#include <MFC/ppmfc_cstring.h>
#include <GlobalVars.h>
#include <CINI.h>

#include <set>

#include "../FA2sp.h"

class Performance
{
public:
    static void UpdateDict();
    static ppmfc::CString GetAvailableIndex();
    static bool NeedsReload;
private:
    static std::set<ppmfc::CString> IndexDict;
};

bool Performance::NeedsReload = true;
std::set<ppmfc::CString> Performance::IndexDict{};

ppmfc::CString Performance::GetAvailableIndex()
{
    ppmfc::CString buffer;
    for (int i = 1000000;; ++i)
    {
        buffer.Format("%08d", i);
        auto itr = Performance::IndexDict.find(buffer); // optimize, not find twice
        if (itr == Performance::IndexDict.end())
        {
            Performance::IndexDict.insert(itr, buffer);
            return buffer;
        }
    }
}

void Performance::UpdateDict()
{
    Performance::IndexDict.clear();

    auto& ini = GlobalVars::INIFiles::CurrentDocument();
    auto LoadTypesValue = [&ini](ppmfc::CString section)
    {
        if (auto pSection = ini.GetSection(section))
            for (auto& pair : pSection->EntitiesDictionary)
                Performance::IndexDict.insert(pair.second);
    };
    auto LoadTypesKey = [&ini](ppmfc::CString section)
    {
        if (auto pSection = ini.GetSection(section))
            for (auto& pair : pSection->EntitiesDictionary)
                Performance::IndexDict.insert(pair.first);
    };
    LoadTypesValue("ScriptTypes");
    LoadTypesValue("Taskforces");
    LoadTypesValue("TeamTypes");
    LoadTypesKey("Triggers");
    LoadTypesKey("Events");
    LoadTypesKey("Tags");
    LoadTypesKey("Actions");
    LoadTypesKey("AITriggerTypes");

    Performance::NeedsReload = false;
}

//DEFINE_HOOK(49EDD3, CMapData_LoadMap_UpdateDict, 6)
//{
//    Performance::NeedsReload = true;
//    return 0;
//}
//
//DEFINE_HOOK(446520, Miscs_GetAvailableIndex, 7)
//{
//    if (ExtConfigs::FastAvailableIndex)
//    {
//        GET_STACK(ppmfc::CString*, pString, 0x4);
//
//        if (Performance::NeedsReload)
//            Performance::UpdateDict();
//
//        new(pString) ppmfc::CString(Performance::GetAvailableIndex());
//
//        return 0x446FB3;
//    }
//    return 0;
//}