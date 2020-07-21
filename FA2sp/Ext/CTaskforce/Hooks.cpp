#include <Helpers/Macro.h>
#include "Body.h"

DEFINE_HOOK(4E41A0, CTaskForce_OnMemberEditChanged, 6)
{
	GET(CTaskForce* const, pThis, ECX);

	CString windowText;
	pThis->CCBMemberType.GetWindowTextA(windowText);

	return windowText.GetLength() ? 0 : 0x4E4539;
}