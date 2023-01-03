#include "Body.h"

#include <Helpers/Macro.h>

DEFINE_HOOK(502E66, CTriggerOption_OnInitDialog_RepeatTypeFix, 7)
{
    GET(CTriggerOption*, pThis, ESI);

    pThis->CCBHouse.DeleteAllStrings();
    pThis->CCBRepeatType.DeleteAllStrings();

    pThis->CCBRepeatType.AddString("0 - One Time OR");
    pThis->CCBRepeatType.AddString("1 - One Time AND");
    pThis->CCBRepeatType.AddString("2 - Repeating OR");

    return 0;
}