#pragma once

#include <FA2PP.h>

#include <CIsoView.h>
#include "../FA2Expand.h"

class NOVTABLE CIsoViewExt : public CIsoView
{
public:
    static void ProgramStartupInit();

    BOOL PreTranslateMessageExt(MSG* pMsg);

    BOOL OnMouseWheelExt(UINT Flags, short zDelta, CPoint pt);
};