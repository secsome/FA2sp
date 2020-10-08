#include "MutexHelper.h"

namespace MutexHelper {
	bool Attach(CString MutexVal) {
		_Mutex = CreateMutex(NULL, TRUE, MutexVal);
		DWORD dwError = GetLastError();
		if (_Mutex && dwError != ERROR_ALREADY_EXISTS)
			return true;
		return false;
	}

	void Detach() {
		ReleaseMutex(_Mutex);
	}
}