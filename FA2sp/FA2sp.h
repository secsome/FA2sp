#pragma once

#include "Logger.h"
#include "Ext/FA2Expand.h"
#include "Utils/Replacement.h"

#include <Helpers\Macro.h>

#include <map>

typedef unsigned char byte;

class FA2sp
{
public:
    static HANDLE hInstance;
    static void ExtConfigsInitialize();

    static std::map<CString, CString> StringTableDictionary;
};

class ExtConfigs
{
public:
    static bool OverlayFilter;
    static bool AllowIncludes;
};

