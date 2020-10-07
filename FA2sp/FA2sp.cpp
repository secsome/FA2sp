#include "FA2sp.h"
#include "FA2sp.version.h"

#include <GlobalVars.h>

#include <Structures/FATree.h>
#include <Structures/FAMap.h>

HANDLE FA2sp::hInstance;

//bool ExtConfigs::AllowIncludes = false;
//bool ExtConfigs::OverlayFilter = false;

DEFINE_HOOK(41FC8B, FAData_Config_Init, 5)
{
	FA2sp::ExtConfigsInitialize();
	return 0;
}

void FA2sp::ExtConfigsInitialize()
{
	//INIClass* pFAData = &GlobalVars::INIFiles::FAData.get();
	auto pFAData = reinterpret_cast<std::map<const char*, INISection>*>(0x7EDDDC);
	//ExtConfigs::AllowIncludes = pFAData->GetBool("ExtConfigs", "AllowIncludes");
	//ExtConfigs::OverlayFilter = pFAData->GetBool("ExtConfigs", "OverlayFilter");
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
		//	sprintf_s(pInfo->Message, pInfo->cchMessage, "Found Final Alert 2 version 1.02. Applying FA2sp 2020-07-22.");
		//	return S_OK;
		//}
		//else
		//{
		//	sprintf_s(pInfo->Message, pInfo->cchMessage, "Requires Final Alert 2 version 1.02.");
		//	return S_FALSE;
		//}
		if (pInfo->Message)
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, "Found Final Alert 2 version 1.02. Applying FA2sp 2020-07-22.");
			return S_OK;
		}
	}
	return E_POINTER;
}

DEFINE_HOOK(537129, ExeRun, 9)
{
	Logger::Initialize();
	Logger::Info("Found Final Alert 2 version 1.02. Applying FA2sp 2020-07-22.\n");
	Replacement::String();
	FA2Expand::ExeRun();
	return 0;
}

DEFINE_HOOK(537208, ExeTerminate, 9)
{
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