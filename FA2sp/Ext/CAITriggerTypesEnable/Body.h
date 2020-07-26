#pragma once

#include <CAITriggerTypesEnable.h>
#include "../FA2Expand.h"

class NOVTABLE CAITriggerTypesEnableExt : public CAITriggerTypesEnable
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CAITriggerTypesEnable* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CAITriggerTypesEnableExt() {};
	~CAITriggerTypesEnableExt() {};

private:

};