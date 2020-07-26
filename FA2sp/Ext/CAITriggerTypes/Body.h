#pragma once

#include <CAITriggerTypes.h>
#include "../FA2Expand.h"

class NOVTABLE CAITriggerTypesExt : public CAITriggerTypes
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CAITriggerTypes* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CAITriggerTypesExt() {};
	~CAITriggerTypesExt() {};

private:

};