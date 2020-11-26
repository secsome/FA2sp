#include "FA2sp.h"
#include "FA2sp.Macros.h"

#include "Helpers/MutexHelper.h"

#include <GlobalVars.h>

#include <clocale>

HANDLE FA2sp::hInstance;
std::map<CString, CString> FA2sp::StringTableDictionary;
bool ExtConfigs::OverlayFilter;
bool ExtConfigs::AllowIncludes;

DEFINE_HOOK(41FC8B, FAData_Config_Init, 5)
{
	FA2sp::ExtConfigsInitialize();
	return 0;
}

void FA2sp::ExtConfigsInitialize()
{
	auto pFAData = &GlobalVars::INIFiles::FAData();
	ExtConfigs::AllowIncludes = pFAData->GetBool("ExtConfigs", "AllowIncludes");
	ExtConfigs::OverlayFilter = pFAData->GetBool("ExtConfigs", "OverlayFilter");
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
		//if (pInfo->exeFilesize == 0x1F4000)
		//{
		//	sprintf_s(pInfo->Message, pInfo->cchMessage, APPLY_INFO);
		//	return S_OK;
		//}
		//else
		//{
		//	sprintf_s(pInfo->Message, pInfo->cchMessage, "Requires Final Alert 2 version 1.02.");
		//	return S_FALSE;
		//}
		if (pInfo->Message)
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, APPLY_INFO);
			return S_OK;
		}
	}
	return E_POINTER;
}

DEFINE_HOOK(537129, ExeRun, 9)
{
	MessageBox(NULL, "For Syringe Debug", "", MB_OK);
#ifdef ONLY_ONE
	bool bMutexResult = MutexHelper::Attach(MUTEX_HASH_VAL);
	if (!bMutexResult) {
		MessageBox(nullptr, MUTEX_INIT_ERROR_MSG, MUTEX_INIT_ERROR_TIT, MB_OK);
		ExitProcess(114514u);
	}
#endif
	Logger::Initialize();
	Logger::Info(APPLY_INFO"\n");
	Replacement::String();
	FA2Expand::ExeRun();
	return 0;
}

DEFINE_HOOK(537208, ExeTerminate, 9)
{
#ifdef ONLY_ONE
	MutexHelper::Detach();
#endif
	Logger::Info("FA2sp Terminating...\n");
	Logger::Close();
	GET(UINT, result, EAX);
	ExitProcess(result);
}

#ifdef _DEBUG
// Just for test, lol
DEFINE_HOOK(43273B, ExitMessageBox, 8)
{
	R->EAX(MB_OK);
	return 0x432743;
}
#endif