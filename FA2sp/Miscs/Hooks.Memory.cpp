#include "../RunTime.h"

#include <Helpers/Macro.h>

class MemoryWrapper
{
public:
	static void* __cdecl _malloc(size_t sz)
	{
		return ::malloc(sz);
	}

	static void __cdecl _free(void* ptr)
	{
		::free(ptr);
	}
};

DEFINE_HOOK(537128, ExeStart_MemoryHooks, 5)
{
	RunTime::ResetMemoryContentAt(0x591110, ::HeapFree);
	RunTime::ResetMemoryContentAt(0x591128, ::HeapReAlloc);
	RunTime::ResetMemoryContentAt(0x59112C, ::HeapAlloc);
	RunTime::ResetMemoryContentAt(0x591138, ::HeapSize);
	RunTime::ResetMemoryContentAt(0x591154, ::HeapDestroy);
	RunTime::ResetMemoryContentAt(0x591158, ::HeapCreate);

	RunTime::SetJump(0x536106, (DWORD)MemoryWrapper::_free);
	RunTime::SetJump(0x537CA0, (DWORD)MemoryWrapper::_malloc);

	return 0;
}
