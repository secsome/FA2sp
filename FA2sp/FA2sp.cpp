#include "FA2sp.h"

HANDLE FA2sp::hInstance;

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
		if (pInfo->Message) {
			sprintf_s(pInfo->Message, pInfo->cchMessage, "Found FA2Copy Module");
		}
		return S_OK;
	}
	return E_POINTER;
}

DEFINE_HOOK(537129, ExeRun, 9)
{
	Logger::Initialize();
	Logger::Info("FA2Copy - Inline Version Applied. Version 0.1\n");
	Replacement::String();
	FA2Expand::ExeRun();

#ifdef _DEBUG
	MessageBox(NULL, "Applying FA2Copy-IL DEBUG version\nSeveral functions might be unstable", "Debug Warning", MB_OK);

#endif

	return 0;
}

DEFINE_HOOK(537208, ExeTerminate, 9)
{
	Logger::Info("FA2Copy - Inline Version Terminating...\n");
	Logger::Close();
	GET(UINT, result, EAX);
	ExitProcess(result);
}

#ifdef _DEBUG
// Just for test, lol
DEFINE_HOOK(43273E, ExitMessageBox, 5)
{
	R->EAX(MB_OK);
	return 0x432743;
}
#endif