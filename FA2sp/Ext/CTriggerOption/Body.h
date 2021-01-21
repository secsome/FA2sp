#pragma once

#include <CTriggerOption.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerOptionExt : public CTriggerOption
{
public:

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerOptionExt() {};
	~CTriggerOptionExt() {};

private:

};