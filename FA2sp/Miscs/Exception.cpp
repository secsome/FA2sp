#include "Exception.h"
#include "SaveMap.h"

#include "../FA2sp.h"
#include "../FA2sp.Constants.h"

#include <Helpers\Macro.h>

#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>
#include <CLoading.h>
#include <FA2PP.h>

LONG CALLBACK Exception::ExceptionFilter(PEXCEPTION_POINTERS const pExs)
{
	switch (pExs->ExceptionRecord->ExceptionCode) {
	case EXCEPTION_BREAKPOINT:
	case MS_VC_EXCEPTION:
		return EXCEPTION_CONTINUE_SEARCH;
	}

	Exception::ExceptionHandler(pExs);
}

#pragma warning(push)
#pragma warning(disable: 4646) // this function does not return, though it isn't declared VOID

[[noreturn]] LONG CALLBACK Exception::ExceptionHandler(PEXCEPTION_POINTERS const pExs)
{
	Logger::Raw("Exception handler fired!\n");
	Logger::Raw("Exception %X at %p\n", pExs->ExceptionRecord->ExceptionCode, pExs->ExceptionRecord->ExceptionAddress);
	SetWindowText(CFinalSunDlg::Instance->m_hWnd, "Fatal Error - FinalAlert 2");

	Logger::Raw("Last succeeded operation: %d\n", CFinalSunDlg::LastSucceededOperation());
	Logger::Raw("Last succeeded library operation: %d\n", CFinalSunDlg::LastSucceededLibraryOperation());
	Logger::Raw("SE2KMODE: %d\n", CFinalSunDlg::SE2KMODE());

	//	if (IsDebuggerAttached()) return EXCEPTION_CONTINUE_SEARCH;

	switch (pExs->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
	case EXCEPTION_BREAKPOINT:
	case EXCEPTION_DATATYPE_MISALIGNMENT:
	case EXCEPTION_FLT_DENORMAL_OPERAND:
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
	case EXCEPTION_FLT_INEXACT_RESULT:
	case EXCEPTION_FLT_INVALID_OPERATION:
	case EXCEPTION_FLT_OVERFLOW:
	case EXCEPTION_FLT_STACK_CHECK:
	case EXCEPTION_FLT_UNDERFLOW:
	case EXCEPTION_ILLEGAL_INSTRUCTION:
	case EXCEPTION_IN_PAGE_ERROR:
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
	case EXCEPTION_INT_OVERFLOW:
	case EXCEPTION_INVALID_DISPOSITION:
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
	case EXCEPTION_PRIV_INSTRUCTION:
	case EXCEPTION_SINGLE_STEP:
	case EXCEPTION_STACK_OVERFLOW:
	case 0xE06D7363: // exception thrown and not caught
	{
		std::wstring path = Exception::PrepareSnapshotDirectory();

		std::wstring except_file = path + L"\\except.txt";

		if (FILE* except = _wfsopen(except_file.c_str(), L"w", _SH_DENYNO)) {
			constexpr auto const pDelim = "---------------------\n";
			fprintf(except, "Internal Error encountered!\n");
			fprintf(except, pDelim);
			fprintf(except, VERSION_STRVER);
			fprintf(except, "\n");
			fprintf(except, pDelim);

			fprintf(except, "Exception code: %08X at %08p\n", pExs->ExceptionRecord->ExceptionCode, pExs->ExceptionRecord->ExceptionAddress);

			fprintf(except, "Registers:\n");
			PCONTEXT pCtxt = pExs->ContextRecord;
			fprintf(except, "EIP: %08X\tESP: %08X\tEBP: %08X\n", pCtxt->Eip, pCtxt->Esp, pCtxt->Ebp);
			fprintf(except, "EAX: %08X\tEBX: %08X\tECX: %08X\n", pCtxt->Eax, pCtxt->Ebx, pCtxt->Ecx);
			fprintf(except, "EDX: %08X\tESI: %08X\tEDI: %08X\n", pCtxt->Edx, pCtxt->Esi, pCtxt->Edi);

			fprintf(except, "\nStack dump:\n");
			DWORD* ptr = reinterpret_cast<DWORD*>(pCtxt->Esp);
			for (int i = 0; i < 0x100; ++i) {
				fprintf(except, "%08p: %08X\n", ptr, *ptr);
				++ptr;
			}

			fclose(except);
			Logger::Raw("Exception data has been saved to file:\n%ls\n", except_file.c_str());
		}

		if (MessageBox(CFinalSunDlg::Instance->m_hWnd, "FinalAlert 2 has encountered a fatal error!\nWould you like to create a full crash report for the developer?", "Fatal Error!", MB_YESNO | MB_ICONERROR) == IDYES) {
			HCURSOR loadCursor = LoadCursor(nullptr, IDC_WAIT);
			SetClassLong(CFinalSunDlg::Instance->m_hWnd, GCL_HCURSOR, reinterpret_cast<LONG>(loadCursor));
			SetCursor(loadCursor);
			Logger::Raw("Making a memory dump\n");

			MINIDUMP_EXCEPTION_INFORMATION expParam;
			expParam.ThreadId = GetCurrentThreadId();
			expParam.ExceptionPointers = pExs;
			expParam.ClientPointers = FALSE;

			Exception::FullDump(std::move(path), &expParam);

			loadCursor = LoadCursor(nullptr, IDC_ARROW);
			SetClassLong(CFinalSunDlg::Instance->m_hWnd, GCL_HCURSOR, reinterpret_cast<LONG>(loadCursor));
			SetCursor(loadCursor);
		}
		break;
	}
	case ERROR_MOD_NOT_FOUND:
	case ERROR_PROC_NOT_FOUND:
		Logger::Raw("Massive failure: Procedure or module not found!\n");
		break;
	default:
		Logger::Raw("Massive failure: reason unknown, have fun figuring it out\n");
		//			return EXCEPTION_CONTINUE_SEARCH;
		break;
	}

	Logger::Raw("Trying to save current map.\n");
	ppmfc::CString fcrash_backup = CFinalSunApp::ExePath();
	fcrash_backup += "\\fcrash_backup.map";

	SaveMapExt::IsAutoSaving = true;
	CFinalSunDlg::Instance->SaveMap(fcrash_backup);
	SaveMapExt::IsAutoSaving = false;

	MessageBox(CFinalSunDlg::Instance->m_hWnd, "Current MapData has been saved as fcrash_backup.map.", "Fatal Error!", MB_OK | MB_ICONINFORMATION);
	CLoading::Instance->Release();

	CINI::Rules->Release();
	CINI::Ai->Release();
	CINI::Art->Release();
	CINI::Temperate->Release();
	CINI::Snow->Release();
	CINI::Urban->Release();
	CINI::CurrentDocument->Release();
	CINI::Sound->Release();
	CINI::Turtorial->Release();
	CINI::FAData->Release();
	CINI::FALanguage->Release();

	Exception::Exit(pExs->ExceptionRecord->ExceptionCode);
};

#pragma warning(pop)

std::wstring Exception::PrepareSnapshotDirectory() {
	wchar_t path[MAX_PATH];
	auto const len = GetCurrentDirectoryW(MAX_PATH, path);
	std::wstring buffer(path, path + len);

	buffer += L"\\debug";
	CreateDirectoryW(buffer.c_str(), nullptr);

	SYSTEMTIME time;
	GetLocalTime(&time);

	wchar_t subpath[64];
	swprintf(subpath, 64, L"\\snapshot-%04u%02u%02u-%02u%02u%02u", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	buffer += subpath;
	CreateDirectoryW(buffer.c_str(), nullptr);

	return buffer;
}

std::wstring Exception::FullDump(
	PMINIDUMP_EXCEPTION_INFORMATION const pException)
{
	return Exception::FullDump(PrepareSnapshotDirectory(), pException);
}

std::wstring Exception::FullDump(
	std::wstring destinationFolder,
	PMINIDUMP_EXCEPTION_INFORMATION const pException)
{
	std::wstring filename = std::move(destinationFolder);
	filename += L"\\extcrashdump.dmp";

	HANDLE dumpFile = CreateFileW(filename.c_str(), GENERIC_WRITE,
		0, nullptr, CREATE_ALWAYS, FILE_FLAG_RANDOM_ACCESS, nullptr);

	MINIDUMP_TYPE type = static_cast<MINIDUMP_TYPE>(MiniDumpWithFullMemory);

	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), dumpFile, type, pException, nullptr, nullptr);
	CloseHandle(dumpFile);

	return filename;
}

[[noreturn]] void Exception::Exit(UINT ExitCode) {
	Logger::Raw("Exiting...\n");
	ExitProcess(ExitCode);
}

DEFINE_HOOK(435270, CFinalSunDlg_DoModal, 8)
{
	GET(CFinalSunDlg*, pThis, ECX);

	::SetUnhandledExceptionFilter(Exception::ExceptionFilter);
	Logger::Info("FA2sp UnhandledExceptionFliter installed!\n");

	if (DebugActiveProcessStop(GetCurrentProcessId()))
	{
		WinExec("taskkill /IM Syringe.exe /F", SW_HIDE);
		Logger::Info("Syringe detached!\n");
	}
	else
		Logger::Warn("Failed to detach Syringe! Error code = %X!\n", GetLastError());
	
	R->EAX(pThis->FA2CDialog::DoModal());

	return 0x435286;
}