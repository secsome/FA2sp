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

    static std::map<std::string, std::string> TutorialTextsMap;
};

class ExtConfigs
{
public:
    static bool BrowserRedraw;
    static int  BrowserRedraw_GuessMode;
    static bool BrowserRedraw_CleanUp;
    static bool AllowIncludes;
    static bool AllowPlusEqual;
    static bool Stringtables;
    static bool TutorialTexts_Hide;
    static bool TutorialTexts_Fix;
    static bool SortByTriggerName;
    static bool AdjustDropdownWidth;
    static int AdjustDropdownWidth_Factor;
    static int AdjustDropdownWidth_Max;
    static int CopySelectionBound_Color;
    static int CursorSelectionBound_Color;
    static int CursorSelectionBound_HeightColor;
    static bool ExtWaypoints;
};

