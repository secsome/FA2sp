#include <Helpers/Macro.h>
#include "Body.h"

DEFINE_HOOK(4E41A0, CTaskforce_OnCBMemberTypeEditChanged, 6)
{
	GET(CTaskForce*, pThis, ECX);

	return pThis->CCBMemberType.GetWindowTextLength() ? 0 : 0x4E4539;
}