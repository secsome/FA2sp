#pragma once

#include <CTriggerEvent.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerEventExt : public CTriggerEvent
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTriggerEvent* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerEventExt() {};
	~CTriggerEventExt() {};

private:

};