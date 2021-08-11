#pragma once
#include <FA2PP.h>

class MutexHelper{
public:
	static bool Attach(const char* MutexVal);
	static void Detach();
	static HANDLE _Mutex;
};

