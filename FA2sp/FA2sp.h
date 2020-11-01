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

class ExtConfigs
{
public:
    static bool OverlayFilter;
    static bool AllowIncludes;
};

