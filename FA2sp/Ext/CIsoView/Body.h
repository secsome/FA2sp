#pragma once

#include <FA2PP.h>

#include "../FA2Expand.h"

class CIsoView : public FA2CView
{
public:

};

class NOVTABLE CIsoViewExt : public CIsoView
{
public:
    static void ProgramStartupInit();

    BOOL PreTranslateMessageExt(MSG* pMsg);
};