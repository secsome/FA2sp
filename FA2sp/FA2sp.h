#pragma once

#include "Logger.h"
#include "Ext/FA2Expand.h"
#include "Helpers/MultimapHelper.h"

#include <Helpers/Macro.h>
#include <MFC/ppmfc_cstring.h>

#include <map>

typedef unsigned char byte;

class FA2sp
{
public:
    static HANDLE hInstance;
    static std::string STDBuffer;
    static ppmfc::CString Buffer;
    static std::map<ppmfc::CString, ppmfc::CString> TutorialTextsMap;
    static void* pExceptionHandler;

    static void ExtConfigsInitialize();
};

class ExtConfigs
{
public:
    static bool BrowserRedraw;
    static int  BrowserRedraw_GuessMode;
    static bool BrowserRedraw_CleanUp;
    static bool BrowserRedraw_SafeHouses;
    static bool AllowIncludes;
    static bool AllowPlusEqual;
    static bool TutorialTexts_Hide;
    static bool TutorialTexts_Fix;
    static bool SortByTriggerName;
    static bool AdjustDropdownWidth;
    static int AdjustDropdownWidth_Factor;
    static int AdjustDropdownWidth_Max;
    static int CopySelectionBound_Color;
    static int CursorSelectionBound_Color;
    static int CursorSelectionBound_HeightColor;
    static int Waypoint_Color;
    static bool Waypoint_Background;
    static int Waypoint_Background_Color;
    static CPoint Waypoint_Text_ExtraOffset;
    static bool ExtWaypoints;
    static int UndoRedoLimit;
    static bool UseRGBHouseColor;
    static bool SaveMap_AutoSave;
    static int SaveMap_AutoSave_Interval;
    static int SaveMap_AutoSave_MaxCount;
    static bool SaveMap_OnlySaveMAP;
    static int SaveMap_DefaultPreviewOptionMP;
    static int SaveMap_DefaultPreviewOptionSP;
    static bool VerticalLayout;
    static bool FastResize;
    static int RecentFileLimit;
    static int MultiSelectionColor;
    static bool RandomTerrainObjects;
    static int MaxVoxelFacing;
    static bool DDrawInVideoMem;
    static bool DDrawEmulation;
    static bool NoHouseNameTranslation;
};

class Variables
{
public:
    static MultimapHelper Rules;
    static MultimapHelper FAData;
};