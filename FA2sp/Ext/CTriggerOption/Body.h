#pragma once

#include <CTriggerOption.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerOptionExt : public CTriggerOption
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTriggerOption* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerOptionExt() {};
	~CTriggerOptionExt() {};

private:

};