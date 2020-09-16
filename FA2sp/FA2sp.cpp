#include "FA2sp.h"
#include "FA2sp.version.h"

#include <GlobalVars.h>

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
		/*if (pInfo->exeFilesize == 0x3EDB6BD4)
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, "Found Final Alert 2 version 1.02. Applying FA2sp 2020-07-22.");
			return S_OK;
		}
		else
		{
			sprintf_s(pInfo->Message, pInfo->cchMessage, "Requires Final Alert 2 version 1.02.");
			return S_FALSE;
		}*/
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

#ifdef _DEBUG
	MessageBox(NULL, "Found Final Alert 2 version 1.02.\n Applying FA2sp DEBUGGING version.", VERSION_PREFIX VERSION_STR, MB_OK);

#endif

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
DEFINE_HOOK(43273E, ExitMessageBox, 5)
{
	R->EAX(MB_OK);
	return 0x432743;
}

//DEFINE_HOOK(40A016, sub_40A010, 6)
//{
//	GET_STACK(INT, iUkn, STACK_OFFS(0x10, -0x4));
//	GET_STACK(CString*, lpKey, STACK_OFFS(0x10, -0x8));
//
//	Logger::Debug(__FUNCTION__" %X %s\n", iUkn, *lpKey);
//
//	return 0;
//}

/*
DEFINE_HOOK(40A075, sub_40A010_return, 5)
{
	GET(INT, iResult, EAX);
	Logger::Debug("sub_40A010 returned %X as result TYPE\n");
	return 0;
}

DEFINE_HOOK_AGAIN(40A0A8, sub_40A010_return, 5);
DEFINE_HOOK_AGAIN(40A0EA, sub_40A010_return, 5);
DEFINE_HOOK_AGAIN(40A101, sub_40A010_return, 5);
*/

//DEFINE_HOOK(407DA6, sub_407DA0, 6)
//{
//	GET_STACK(INT, arg_0, STACK_OFFS(0x10, -0x4));
//	GET_STACK(LPCSTR, lpSection, STACK_OFFS(0x10, -0x8));
//
//	Logger::Debug(__FUNCTION__" %X %s\n", arg_0, lpSection);
//
//	return 0;
//}



//DEFINE_HOOK(408054, sub_407EA0_return, 8) // INI::GetSection
//{
//	GET(CString*, lpResult, EAX);
//
//	Logger::Debug(__FUNCTION__" %s\n", *lpResult);
//
//	return 0;
//}


/*
DEFINE_HOOK(4032E0, StringPairCallerDebug, 7)
{
	GET_STACK(DWORD, CallAddress, 0x0);
	CallAddress - reinterpret_cast<DWORD>(FA2sp::hInstance) + 0x10000000;
	Logger::Raw("0X%8X\n", CallAddress);
	return 0;
}
*/

//DEFINE_HOOK(4032E0, StringPairDTORDebugger, 7)
//{
//	GET_STACK(DWORD, dwCallAddress, 0x0);
//	dwCallAddress - reinterpret_cast<DWORD>(FA2sp::hInstance) + 0x10000000;
//#include <INI.h>
//	GET(CStringPair*, pThis, ECX);
//	Logger::Info(__FUNCTION__" Caller Address:0x%6X , Key = %s, Value = %s\n", dwCallAddress, pThis->Key, pThis->Value);
//	return 0;
//}

#endif