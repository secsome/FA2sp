#include "../RunTime.h"

#include <Helpers/Macro.h>

DEFINE_HOOK(537128, ExeStart_MemoryHooks, 5)
{
	RunTime::ResetMemoryContentAt(0x591110, HeapFree);
	RunTime::ResetMemoryContentAt(0x591128, HeapReAlloc);
	RunTime::ResetMemoryContentAt(0x59112C, HeapAlloc);
	RunTime::ResetMemoryContentAt(0x591138, HeapSize);
	RunTime::ResetMemoryContentAt(0x591154, HeapDestroy);
	RunTime::ResetMemoryContentAt(0x591158, HeapCreate);

	return 0;
}