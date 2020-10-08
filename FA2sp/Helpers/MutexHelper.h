#pragma once
#include <FA2PP.h>

namespace MutexHelper{
	bool Attach(CString MutexVal);
	void Detach();
	static HANDLE _Mutex;
};

