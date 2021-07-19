#pragma once

#include <CAITriggerEnable.h>
#include "../FA2Expand.h"

class NOVTABLE CAITriggerEnableExt : public CAITriggerEnable
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CAITriggerEnable* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CAITriggerEnableExt() {};
	~CAITriggerEnableExt() {};

private:

};