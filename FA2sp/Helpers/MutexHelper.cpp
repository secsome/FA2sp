#include "MutexHelper.h"

HANDLE MutexHelper::_Mutex = INVALID_HANDLE_VALUE;

bool MutexHelper::Attach(const char* MutexVal) {
	_Mutex = CreateMutex(NULL, TRUE, MutexVal);
	DWORD dwError = GetLastError();
	if (_Mutex && dwError != ERROR_ALREADY_EXISTS)
		return true;
	return false;
}

void MutexHelper::Detach() {
	ReleaseMutex(_Mutex);
}