#pragma once

#include <CPropertyInfantry.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyInfantryExt : public CPropertyInfantry
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

private:

};