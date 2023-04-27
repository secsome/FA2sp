#include "FA2sp.h"
#include "FA2sp.Constants.h"

#include "Helpers/MutexHelper.h"
#include "Miscs/Palettes.h"
#include "Miscs/VoxelDrawer.h"
#include "Miscs/Exception.h"

#include <CINI.h>

#include <clocale>
#include <algorithm>

HANDLE FA2sp::hInstance;
std::string FA2sp::STDBuffer;
ppmfc::CString FA2sp::Buffer;
std::map<ppmfc::CString, ppmfc::CString> FA2sp::TutorialTextsMap;
void* FA2sp::pExceptionHandler = nullptr;

bool ExtConfigs::BrowserRedraw;
int	 ExtConfigs::BrowserRedraw_GuessMode;
bool ExtConfigs::BrowserRedraw_CleanUp;
bool ExtConfigs::BrowserRedraw_SafeHouses;
bool ExtConfigs::AllowIncludes;
bool ExtConfigs::AllowPlusEqual;
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
CPoint ExtConfigs::Waypoint_Text_ExtraOffset;
bool ExtConfigs::ExtWaypoints;
int ExtConfigs::UndoRedoLimit;
bool ExtConfigs::UseRGBHouseColor;
bool ExtConfigs::SaveMap_AutoSave;
int ExtConfigs::SaveMap_AutoSave_Interval;
int ExtConfigs::SaveMap_AutoSave_MaxCount;
bool ExtConfigs::SaveMap_OnlySaveMAP;
int ExtConfigs::SaveMap_DefaultPreviewOptionMP;
int ExtConfigs::SaveMap_DefaultPreviewOptionSP;
bool ExtConfigs::VerticalLayout;
bool ExtConfigs::FastResize;
int ExtConfigs::RecentFileLimit;
int ExtConfigs::MultiSelectionColor;
bool ExtConfigs::RandomTerrainObjects;
int ExtConfigs::MaxVoxelFacing;
bool ExtConfigs::DDrawInVideoMem;
bool ExtConfigs::DDrawEmulation;
bool ExtConfigs::NoHouseNameTranslation;
bool ExtConfigs::EnableMultiSelection;
bool ExtConfigs::ExtendedValidationNoError;

MultimapHelper Variables::Rules = { &CINI::Rules(), &CINI::CurrentDocument() };
MultimapHelper Variables::FAData = { &CINI::FAData() };

void FA2sp::ExtConfigsInitialize()
{	
	ExtConfigs::BrowserRedraw = CINI::FAData->GetBool("ExtConfigs", "BrowserRedraw");
	ExtConfigs::BrowserRedraw_GuessMode = CINI::FAData->GetInteger("ExtConfigs", "BrowserRedraw.GuessMode", 0);
	ExtConfigs::BrowserRedraw_CleanUp = CINI::FAData->GetBool("ExtConfigs", "BrowserRedraw.CleanUp");
	ExtConfigs::BrowserRedraw_SafeHouses = CINI::FAData->GetBool("ExtConfigs", "BrowserRedraw.SafeHouses");
	
	ExtConfigs::AllowIncludes = CINI::FAData->GetBool("ExtConfigs", "AllowIncludes");
	ExtConfigs::AllowPlusEqual = CINI::FAData->GetBool("ExtConfigs", "AllowPlusEqual");

	ExtConfigs::TutorialTexts_Hide = CINI::FAData->GetBool("ExtConfigs", "TutorialTexts.Hide");
	ExtConfigs::TutorialTexts_Fix = CINI::FAData->GetBool("ExtConfigs", "TutorialTexts.Fix");
	
	ExtConfigs::SortByTriggerName = CINI::FAData->GetBool("ExtConfigs", "SortByTriggerName");
	
	ExtConfigs::AdjustDropdownWidth = CINI::FAData->GetBool("ExtConfigs", "AdjustDropdownWidth");
	ExtConfigs::AdjustDropdownWidth_Factor = CINI::FAData->GetInteger("ExtConfigs", "AdjustDropdownWidth.Factor", 8);
	ExtConfigs::AdjustDropdownWidth_Max = CINI::FAData->GetInteger("ExtConfigs", "AdjustDropdownWidth.Max", 360);

	ExtConfigs::CopySelectionBound_Color = 
		CINI::FAData->GetColor("ExtConfigs", "CopySelectionBound.Color", 0x0000FF);
	ExtConfigs::CursorSelectionBound_Color =
		CINI::FAData->GetColor("ExtConfigs", "CursorSelectionBound.Color", 0x3CA03C);
	ExtConfigs::CursorSelectionBound_HeightColor = 
		CINI::FAData->GetColor("ExtConfigs", "CursorSelectionBound.HeightIndicatorColor", 0x3C3C3C);

	ExtConfigs::Waypoint_Color = CINI::FAData->GetColor("ExtConfigs", "Waypoint.Color", 0xFF0000);
	ExtConfigs::Waypoint_Background = CINI::FAData->GetBool("ExtConfigs", "Waypoint.Background");
	ExtConfigs::Waypoint_Background_Color = CINI::FAData->GetColor("ExtConfigs", "Waypoint.Background.Color", 0xFFFFFF);

	ExtConfigs::Waypoint_Text_ExtraOffset = CINI::FAData->GetPoint("ExtConfigs", "Waypoint.Text.ExtraOffset");

	ExtConfigs::ExtWaypoints = CINI::FAData->GetBool("ExtConfigs", "ExtWaypoints");

	ExtConfigs::UndoRedoLimit = CINI::FAData->GetInteger("ExtConfigs", "UndoRedoLimit", 16);

	ExtConfigs::UseRGBHouseColor = CINI::FAData->GetBool("ExtConfigs", "UseRGBHouseColor");

	if (ExtConfigs::SaveMap_AutoSave = CINI::FAData->GetBool("ExtConfigs", "SaveMap.AutoSave"))
	{
		ExtConfigs::SaveMap_AutoSave_Interval = CINI::FAData->GetInteger("ExtConfigs", "SaveMap.AutoSave.Interval", 300);
		ExtConfigs::SaveMap_AutoSave_MaxCount = CINI::FAData->GetInteger("ExtConfigs", "SaveMap.AutoSave.MaxCount", 10);
	}
	else
	{
		ExtConfigs::SaveMap_AutoSave_Interval = -1;
	}
	ExtConfigs::SaveMap_OnlySaveMAP = CINI::FAData->GetBool("ExtConfigs", "SaveMap.OnlySaveMAP");
	ExtConfigs::SaveMap_DefaultPreviewOptionMP = CINI::FAData->GetInteger("ExtConfigs", "SaveMap.DefaultPreviewOptionMP", 0);
	ExtConfigs::SaveMap_DefaultPreviewOptionSP = CINI::FAData->GetInteger("ExtConfigs", "SaveMap.DefaultPreviewOptionSP", 1);

	ExtConfigs::VerticalLayout = CINI::FAData->GetBool("ExtConfigs", "VerticalLayout");

	ExtConfigs::FastResize = CINI::FAData->GetBool("ExtConfigs", "FastResize");

	ExtConfigs::RecentFileLimit = std::clamp(CINI::FAData->GetInteger("ExtConfigs", "RecentFileLimit"), 4, 9);

	ExtConfigs::MultiSelectionColor = CINI::FAData->GetColor("ExtConfigs", "MultiSelectionColor", 0x00FF00);

	ExtConfigs::RandomTerrainObjects = CINI::FAData->GetBool("ExtConfigs", "RandomTerrainObjects");

	ExtConfigs::MaxVoxelFacing = CINI::FAData->GetInteger("ExtConfigs", "MaxVoxelFacing", 8);
	auto Int2Highest = [](unsigned int v)
	{
		unsigned int r; // result of log2(v) will go here
		unsigned int shift;

		r = static_cast<unsigned int>(v > 0xFFFF) << 4; v >>= r;
		shift = static_cast<unsigned int>(v > 0xFF) << 3; v >>= shift; r |= shift;
		shift = static_cast<unsigned int>(v > 0xF) << 2; v >>= shift; r |= shift;
		shift = static_cast<unsigned int>(v > 0x3) << 1; v >>= shift; r |= shift;
		r |= (v >> 1);
		return r;
	};
	ExtConfigs::MaxVoxelFacing = 1 << Int2Highest(ExtConfigs::MaxVoxelFacing);
	if (ExtConfigs::MaxVoxelFacing < 8)
		ExtConfigs::MaxVoxelFacing = 8;
	else if (ExtConfigs::MaxVoxelFacing > 256)
		ExtConfigs::MaxVoxelFacing = 256;

	// Disable it for now
	ExtConfigs::MaxVoxelFacing = 8;

	ExtConfigs::DDrawInVideoMem = CINI::FAData->GetBool("ExtConfigs", "DDrawInVideoMem", true);
	ExtConfigs::DDrawEmulation = CINI::FAData->GetBool("ExtConfigs", "DDrawEmulation");

	ExtConfigs::NoHouseNameTranslation = CINI::FAData->GetBool("ExtConfigs", "NoHouseNameTranslation");

	ExtConfigs::EnableMultiSelection = CINI::FAData->GetBool("ExtConfigs", "EnableMultiSelection");

	ExtConfigs::ExtendedValidationNoError = CINI::FAData->GetBool("ExtConfigs", "ExtendedValidationNoError");
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
//SYRINGE_HANDSHAKE(pInfo)
//{
//	if (pInfo) {
//		if (pInfo->)
//		{
//			sprintf_s(pInfo->Message, pInfo->cchMessage, APPLY_INFO);
//			return S_OK;
//		}
//		else
//		{
//			sprintf_s(pInfo->Message, pInfo->cchMessage, "Requires Official Final Alert 2 version 1.02.");
//			return S_FALSE;
//		}
//	}
//	return E_POINTER;
//}

#define ENABLE_VISUAL_STYLE
static ULONG_PTR ulCookie;

bool DetachFromDebugger();
DEFINE_HOOK(537129, ExeRun, 9)
{
	Logger::Initialize();
	Logger::Info(APPLY_INFO);
	Logger::Wrap(1);

	if (DetachFromDebugger())
		Logger::Info("Syringe detached!\n");
	else
		Logger::Warn("Failed to detach Syringe!\n");

#ifndef NDEBUG
	MessageBox(NULL, APPLY_INFO, PRODUCT_NAME, MB_OK);
	
#endif
	bool bMutexResult = MutexHelper::Attach(MUTEX_HASH_VAL);
	if (!bMutexResult) {
		if (MessageBox(nullptr, MUTEX_INIT_ERROR_MSG, MUTEX_INIT_ERROR_TIT, MB_YESNO | MB_ICONQUESTION) != IDYES)
			ExitProcess(114514);
	}
	
	FA2Expand::ExeRun();
	VoxelDrawer::Initalize();

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
			Logger::Put("Visual Style Enabled!\n");
	}
#endif

	return 0;
}

#include <CLoading.h>

DEFINE_HOOK(47FACE, CLoading_OnInitDialog_ProgramInfo, 7)
{
	GET(CLoading*, pThis, ESI);

	pThis->CSCVersion.SetWindowText(LOADING_VERSION);
	pThis->CSCBuiltby.SetWindowText(LOADING_AUTHOR);
	pThis->SetDlgItemText(1300, LOADING_WEBSITE);

	return 0;
}

#include "Ext/CFinalSunDlg/Body.h"

DEFINE_HOOK(537208, ExeTerminate, 9)
{
	MutexHelper::Detach();
	Logger::Info("FA2sp Terminating...\n");
	Logger::Close();
	VoxelDrawer::Finalize();

	// Destruct static ppmfc stuffs here
	CViewObjectsExt::OnExeTerminate();

#ifdef ENABLE_VISUAL_STYLE
	::DeactivateActCtx(NULL, ulCookie);
#endif

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

#include <tlhelp32.h>
// https://stackoverflow.com/questions/70458828
bool DetachFromDebugger()
{
	using NTSTATUS = LONG;

	auto GetDebuggerProcessId = [](DWORD dwSelfProcessId) -> DWORD
	{
		DWORD dwParentProcessId = -1;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(2, 0);
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &pe32);
		do
		{
			if (pe32.th32ProcessID == dwSelfProcessId)
			{
				dwParentProcessId = pe32.th32ParentProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));
		CloseHandle(hSnapshot);
		return dwParentProcessId;
	};

	HMODULE hModule = LoadLibrary("ntdll.dll");
	if (hModule != NULL)
	{
		auto const NtRemoveProcessDebug =
			(NTSTATUS(__stdcall*)(HANDLE, HANDLE))GetProcAddress(hModule, "NtRemoveProcessDebug");
		auto const NtSetInformationDebugObject =
			(NTSTATUS(__stdcall*)(HANDLE, ULONG, PVOID, ULONG, PULONG))GetProcAddress(hModule, "NtSetInformationDebugObject");
		auto const NtQueryInformationProcess =
			(NTSTATUS(__stdcall*)(HANDLE, ULONG, PVOID, ULONG, PULONG))GetProcAddress(hModule, "NtQueryInformationProcess");
		auto const NtClose =
			(NTSTATUS(__stdcall*)(HANDLE))GetProcAddress(hModule, "NtClose");

		HANDLE hDebug;
		HANDLE hCurrentProcess = GetCurrentProcess();
		NTSTATUS status = NtQueryInformationProcess(hCurrentProcess, 30, &hDebug, sizeof(HANDLE), 0);
		if (0 <= status)
		{
			ULONG killProcessOnExit = FALSE;
			status = NtSetInformationDebugObject(
				hDebug,
				1,
				&killProcessOnExit,
				sizeof(ULONG),
				NULL
			);
			if (0 <= status)
			{
				const auto pid = GetDebuggerProcessId(GetProcessId(hCurrentProcess));
				status = NtRemoveProcessDebug(hCurrentProcess, hDebug);
				if (0 <= status)
				{
					HANDLE hDbgProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
					if (INVALID_HANDLE_VALUE != hDbgProcess)
					{
						BOOL ret = TerminateProcess(hDbgProcess, EXIT_SUCCESS);
						CloseHandle(hDbgProcess);
						return ret;
					}
				}
			}
			NtClose(hDebug);
		}
		FreeLibrary(hModule);
	}

	return false;
}