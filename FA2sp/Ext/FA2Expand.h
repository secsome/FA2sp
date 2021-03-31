#pragma once

#include "../Logger.h"
#include "../RunTime.h"

#include <Helpers/Macro.h>
#include "../StaticPatcher.Macro.h"

class FA2Expand
{
public:
	static void __stdcall ExeRun();

	FA2Expand();
	~FA2Expand();
};