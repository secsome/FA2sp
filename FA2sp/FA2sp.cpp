#include "FA2sp.h"
#include "FA2sp.Constants.h"

#include "Helpers/MutexHelper.h"
#include "Miscs/Palettes.h"
#include "Miscs/DrawStuff.h"

#include <GlobalVars.h>
#include <CINI.h>

#include <clocale>

HANDLE FA2sp::hInstance;
ppmfc::CString FA2sp::Buffer;
std::map<ppmfc::CString, ppmfc::CString> FA2sp::TutorialTextsMap;

bool ExtConfigs::BrowserRedraw;
int	 ExtConfigs::BrowserRedraw_GuessMode;
bool ExtConfigs::BrowserRedraw_CleanUp;
bool ExtConfigs::AllowIncludes;
bool ExtConfigs::AllowPlusEqual;
bool ExtConfigs::Stringtables;
bool ExtConfigs::TutorialTexts_Hide;
bool ExtConfigs::TutorialTexts_Fix;
bool ExtConfigs::SortByTriggerName;
bool ExtConfigs::AdjustDropdownWidth;
int ExtConfigs::AdjustDropdownWidth_Factor;
int ExtConfigs::AdjustDropdownWidth_Max;
int ExtConfigs::CopySelectionBound_Color;
int ExtConfigs::CursorSelectionBound_Color;
int ExtConfigs::CursorSelectionBound_HeightColor;
int ExtConfigs::Waypoint_Color;
bool ExtConfigs::Waypoint_Background;
int ExtConfigs::Waypoint_Background_Color;
bool ExtConfigs::ExtWaypoints;
int ExtConfigs::UndoRedoLimit;
bool ExtConfigs::UseRGBHouseColor;

MultimapHelper Variables::Rules = { &GlobalVars::INIFiles::Rules(), &GlobalVars::INIFiles::CurrentDocument() };

DEFINE_HOOK(41FC8B, FAData_Config_Init, 5)
{
	FA2sp::ExtConfigsInitialize();
	return 0;
}

void FA2sp::ExtConfigsInitialize()
{
	auto& fadata = GlobalVars::INIFiles::FAData();
	
	ExtConfigs::BrowserRedraw = fadata.GetBool("ExtConfigs", "BrowserRedraw");
	ExtConfigs::BrowserRedraw_GuessMode = fadata.GetInteger("ExtConfigs", "BrowserRedraw.GuessMode", 0);
	ExtConfigs::BrowserRedraw_CleanUp = fadata.GetBool("ExtConfigs", "BrowserRedraw.CleanUp");
	
	ExtConfigs::AllowIncludes = fadata.GetBool("ExtConfigs", "AllowIncludes");
	ExtConfigs::AllowPlusEqual = fadata.GetBool("ExtConfigs", "AllowPlusEqual");
	
	ExtConfigs::Stringtables = fadata.GetBool("ExtConfigs", "Stringtables");
	ExtConfigs::TutorialTexts_Hide = fadata.GetBool("ExtConfigs", "TutorialTexts.Hide");
	ExtConfigs::TutorialTexts_Fix = fadata.GetBool("ExtConfigs", "TutorialTexts.Fix");
	
	ExtConfigs::SortByTriggerName = fadata.GetBool("ExtConfigs", "SortByTriggerName");
	
	ExtConfigs::AdjustDropdownWidth = fadata.GetBool("ExtConfigs", "AdjustDropdownWidth");
	ExtConfigs::AdjustDropdownWidth_Factor = fadata.GetInteger("ExtConfigs", "AdjustDropdownWidth.Factor", 8);
	ExtConfigs::AdjustDropdownWidth_Max = fadata.GetInteger("ExtConfigs", "AdjustDropdownWidth.Max", 360);

	ExtConfigs::CopySelectionBound_Color = 
		fadata.GetColor("ExtConfigs", "CopySelectionBound.Color", 0x0000FF);
	ExtConfigs::CursorSelectionBound_Color =
		fadata.GetColor("ExtConfigs", "CursorSelectionBound.Color", 0x3CA03C);
	ExtConfigs::CursorSelectionBound_HeightColor = 
		fadata.GetColor("ExtConfigs", "CursorSelectionBound.HeightIndicatorColor", 0x3C3C3C);

	ExtConfigs::Waypoint_Color = fadata.GetColor("ExtConfigs", "Waypoint.Color", 0xFF0000);
	ExtConfigs::Waypoint_Background = fadata.GetBool("ExtConfigs", "Waypoint.Background");
	ExtConfigs::Waypoint_Background_Color = fadata.GetColor("ExtConfigs", "Waypoint.Background.Color", 0xFFFFFF);

	ExtConfigs::ExtWaypoints = fadata.GetBool("ExtConfigs", "ExtWaypoints");

	ExtConfigs::UndoRedoLimit = fadata.GetInteger("ExtConfigs", "UndoRedoLimit", 16);

	ExtConfigs::UseRGBHouseColor = fadata.GetBool("ExtConfigs", "UseRGBHouseColor");
}

// DllMain
BOOL APIENTRY DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		FA2sp::hInstance = hInstance;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// Export Functions
SYRINGE_HANDSHAKE(pInfo)
{
	if (pInfo) {
		if (pInfo->Message)
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, APPLY_INFO);
			return S_OK;
		}
		else
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, "Requires Official Final Alert 2 version 1.02.");
			return S_FALSE;
		}
	}
	return E_POINTER;
}

DEFINE_HOOK(537129, ExeRun, 9)
{
#ifdef _DEBUG
	// MessageBox(NULL, APPLY_INFO, PRODUCT_NAME, MB_OK);
#endif
	bool bMutexResult = MutexHelper::Attach(MUTEX_HASH_VAL);
	if (!bMutexResult) {
		if (MessageBox(nullptr, MUTEX_INIT_ERROR_MSG, MUTEX_INIT_ERROR_TIT, MB_YESNO | MB_ICONQUESTION) != IDYES)
			ExitProcess(114514);
	}
	Logger::Initialize();
	Logger::Info(APPLY_INFO);
	Logger::Wrap(1);
	FA2Expand::ExeRun();
	DrawStuff::init();
	return 0;
}

DEFINE_HOOK(537208, ExeTerminate, 9)
{
	MutexHelper::Detach();
	Logger::Info("FA2sp Terminating...\n");
	Logger::Close();
	DrawStuff::deinit();
	GET(UINT, result, EAX);
	ExitProcess(result);
}

#ifdef _DEBUG
// Just for test, lol
//DEFINE_HOOK(43273B, ExitMessageBox, 8)
//{
//	R->EAX(MB_OK);
//	return 0x432743;
//}
#endif