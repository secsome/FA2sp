#include "FA2sp.h"

//DEFINE_HOOK(4B5D98, Debug_4AE910_Begin, 5)
//{
//    GET(const char*, pRegName, EAX);
//    if(pRegName)
//        Logger::Debug(__FUNCTION__" pRegName = %s\n", pRegName);
//    return 0;
//}
//
//DEFINE_HOOK(4B5DA3, Debug_4AE910_End, 8)
//{
//    GET(int, nResult, EAX);
//    Logger::Debug(__FUNCTION__" nResult = %d\n", nResult);
//    return 0;
//}