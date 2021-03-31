//#include <GlobalVars.h>
//
//#include <set>
//
//
//using string_type = ppmfc::CString;
//
//class PerformanceFixes
//{
//private:
//    static std::set<string_type, INISectionEntriesComparator> idCollector;
//
//private:
//    static void initializeIdCollector();
//
//public:
//    static void GetAvailableIndex(string_type* pString);
//};
//std::set<string_type, INISectionEntriesComparator> PerformanceFixes::idCollector;
//
//void PerformanceFixes::initializeIdCollector()
//{
//    auto parseKeys = [](const char* pSectionName)
//    {
//        auto& ini = GlobalVars::INIFiles::CurrentDocument();
//        if (auto section = ini.GetSection(pSectionName))
//            for (auto pair : section->EntitiesDictionary)
//                PerformanceFixes::idCollector.insert(pair.first);
//    };
//    parseKeys("Taskforces");
//    parseKeys("Teamtypes");
//    parseKeys("Triggers");
//    parseKeys("Tags");
//    parseKeys("Events");
//    parseKeys("Actions");
//    parseKeys("AITriggerTypes");
//    parseKeys("ScriptTypes");
//}
//
//void PerformanceFixes::GetAvailableIndex(string_type* pString)
//{
//    if (PerformanceFixes::idCollector.size() == 0)
//        PerformanceFixes::initializeIdCollector();
//    auto pid = *PerformanceFixes::idCollector.end();
//    int id;
//    if (sscanf_s(pid, "%d", &id))
//    {
//
//    }
//}
//
//DEFINE_HOOK(446520, Miscs_GetAvailableIndex, 7)
//{
//    GET_STACK(string_type*, pRet, -0x4);
//    PerformanceFixes::GetAvailableIndex(pRet);
//    R->EAX(pRet);
//    return 0x446FB3;
//}