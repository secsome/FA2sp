#pragma once

#include "Logger.h"
#include "Ext/FA2Expand.h"
#include "Utils/Replacement.h"

#include <Helpers\Macro.h>

#include <string>
#include <map>

typedef unsigned char byte;

class FA2sp
{
public:
    static HANDLE hInstance;
    static void ExtConfigsInitialize();

    static std::map<std::string, std::string> WIP_TutorialTextMap;
};

class ExtConfigs
{
public:
    static bool BrowserRedraw;
    static bool OverlayFilter;
    static bool AllowIncludes;
    static bool AllowPlusEqual;
    static bool Stringtables;

    static bool WIP_TutorialTexts;
};

