#pragma once

#include <CPropertyAircraft.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyAircraftExt : public CPropertyAircraft
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

private:

};