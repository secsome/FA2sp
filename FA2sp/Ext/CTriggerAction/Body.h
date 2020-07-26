#pragma once

#include <CTriggerAction.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerActionExt : public CTriggerAction
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTriggerAction* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerActionExt() {};
	~CTriggerActionExt() {};

private:

};