#pragma once

#include "Logger.h"
#include "Ext/FA2Expand.h"
#include "Utils/Replacement.h"
#include <Helpers\Macro.h>

typedef unsigned char byte;

class FA2sp
{
public:
    static HANDLE hInstance;
    static void ExtConfigsInitialize();
};


namespace ExtConfigs
{
    static bool OverlayFilter;
    static bool AllowIncludes;
}

