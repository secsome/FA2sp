#include <Helpers/Macro.h>

// FA2 will no longer automatically change the extension of map
DEFINE_HOOK(42703A, FA2Main_SaveMap_Extension, 9)
{
	return 0x42708D;
}
