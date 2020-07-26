#pragma once

#include "../RunTime.h"

// Replacement also need to be noticed that you cannot overwrite
// some important items, a too long string might cause problems
// So just keep the original length of it is the best choice

class Replacement {
public:
	static void String();
private:

};

#define ReplaceStringAt(newString, address) \
RunTime::ResetMemoryContentAt(address, newString, sizeof newString);