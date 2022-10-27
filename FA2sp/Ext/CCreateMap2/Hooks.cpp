#include <Helpers/Macro.h>
#include <CCreateMap3A.h>

// Issue #22
DEFINE_HOOK(42DF67, CCreateMap2_SkipEnableAITriggers, 7)
{
	return 0x42E0AA;
}