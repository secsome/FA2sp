#include "Body.h"

#include <Helpers/Macro.h>

DEFINE_HOOK(4E41A0, CTaskforce_OnCBMemberTypeEditChanged, 6)
{
	GET(CTaskForce*, pThis, ECX);

	return pThis->CCBMemberType.GetWindowTextLength() ? 0 : 0x4E4539;
}

DEFINE_HOOK(4E48DB, CTaskforce_OnBNAddMemberClicked_SafetyGuard, 6)
{
	GET(CTaskForce*, pThis, ESI);

	return pThis->CLBMembers.GetCount() < 6 ? 0 : 0x4E48FC;
}