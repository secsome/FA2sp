#pragma once

#include <CPropertyBuilding.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyBuildingExt : public CPropertyBuilding
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

private:

};