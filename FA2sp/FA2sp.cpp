#include "FA2sp.h"
#include "FA2sp.Constants.h"

#include "Helpers/MutexHelper.h"
#include "Miscs/Palettes.h"
#include "Miscs/DrawStuff.h"
#include "Miscs/Exception.h"

#include <CINI.h>

#include <clocale>

HANDLE FA2sp::hInstance;
ppmfc::CString FA2sp::Buffer;
std::map<ppmfc::CString, ppmfc::CString> FA2sp::TutorialTextsMap;
void* FA2sp::pExceptionHandler = nullptr;

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
bool ExtConfigs::SaveMap;
bool ExtConfigs::SaveMap_AutoSave;
int ExtConfigs::SaveMap_AutoSave_Interval;
int ExtConfigs::SaveMap_AutoSave_MaxCount;
bool ExtConfigs::SaveMap_OnlySaveMAP;
bool ExtConfigs::VerticalLayout;

MultimapHelper Variables::Rules = { &CINI::Rules(), &CINI::CurrentDocument() };

DEFINE_HOOK(41FC8B, FAData_Config_Init, 5)
{
	FA2sp::ExtConfigsInitialize();
	return 0;
}

void FA2sp::ExtConfigsInitialize()
{
	auto& fadata = CINI::FAData();
	
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

	if (ExtConfigs::SaveMap = fadata.GetBool("ExtConfigs", "SaveMap"))
	{
		if (ExtConfigs::SaveMap_AutoSave = fadata.GetBool("ExtConfigs", "SaveMap.AutoSave"))
		{
			ExtConfigs::SaveMap_AutoSave_Interval = fadata.GetInteger("ExtConfigs", "SaveMap.AutoSave.Interval", 300);
			ExtConfigs::SaveMap_AutoSave_MaxCount = fadata.GetInteger("ExtConfigs", "SaveMap.AutoSave.MaxCount", 10);
		}
		else
		{
			ExtConfigs::SaveMap_AutoSave_Interval = -1;
		}
	}
	ExtConfigs::SaveMap_OnlySaveMAP = fadata.GetBool("ExtConfigs", "SaveMap.OnlySaveMAP");
	
	ExtConfigs::VerticalLayout = fadata.GetBool("ExtConfigs", "VerticalLayout");
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

#define ENABLE_VISUAL_STYLE
static ULONG_PTR ulCookie;

DEFINE_HOOK(537129, ExeRun, 9)
{
#ifdef _DEBUG
	MessageBox(NULL, APPLY_INFO, PRODUCT_NAME, MB_OK);
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

#ifdef ENABLE_VISUAL_STYLE

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
	// GetModuleName
	char ModuleNameBuffer[MAX_PATH];
	GetModuleFileName(static_cast<HMODULE>(FA2sp::hInstance), ModuleNameBuffer, MAX_PATH);
	int nLength = strlen(ModuleNameBuffer);
	int i = nLength - 1;
	for (; i >= 0; --i)
	{
		if (ModuleNameBuffer[i] == '\\')
			break;
	}
	++i;
	int nModuleNameLen = nLength - i;
	memcpy(ModuleNameBuffer, ModuleNameBuffer + i, nModuleNameLen);
	ModuleNameBuffer[nModuleNameLen] = '\0';

	// Codes from 
	// https://referencesource.microsoft.com/#System.Windows.Forms/winforms/Managed/System/WinForms/UnsafeNativeMethods.cs,8197
	ACTCTX enableThemingActivationContext;
	enableThemingActivationContext.cbSize = sizeof ACTCTX;
	enableThemingActivationContext.lpSource = ModuleNameBuffer; // "FA2sp.dll"
	enableThemingActivationContext.lpResourceName = (LPCSTR)101;
	enableThemingActivationContext.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID;
	auto hActCtx = ::CreateActCtx(&enableThemingActivationContext);
	if (hActCtx != INVALID_HANDLE_VALUE)
	{
		if (::ActivateActCtx(hActCtx, &ulCookie))
			Logger::Debug("Visual Style Enabled!\n");
	}
#endif

	/*if (HINSTANCE handle = GetModuleHandle("kernel32.dll")) {
		if (GetProcAddress(handle, "AddVectoredExceptionHandler")) {
			FA2sp::pExceptionHandler = AddVectoredExceptionHandler(1, Exception::ExceptionFilter);
		}
	}*/

	return 0;
}

#include "Ext/CFinalSunDlg/Body.h"

DEFINE_HOOK(537208, ExeTerminate, 9)
{
	MutexHelper::Detach();
	Logger::Info("FA2sp Terminating...\n");
	Logger::Close();
	DrawStuff::deinit();

	// Destruct static ppmfc stuffs here
	ObjectBrowserControlExt::OnExeTerminate();

#ifdef ENABLE_VISUAL_STYLE
	::DeactivateActCtx(NULL, ulCookie);
#endif

	/*if (HINSTANCE handle = GetModuleHandle("kernel32.dll")) {
		if (GetProcAddress(handle, "RemoveVectoredExceptionHandler")) {
			RemoveVectoredExceptionHandler(FA2sp::pExceptionHandler);
			FA2sp::pExceptionHandler = nullptr;
		}
	}*/

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