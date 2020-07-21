#pragma once

#include "../RunTime.h"

#include <array>

class Replacement {
public:
	static void String();
private:

};

#define ReplaceStringAt(newString, address) \
RunTime::ResetMemoryContentAt(address, newString, sizeof newString);