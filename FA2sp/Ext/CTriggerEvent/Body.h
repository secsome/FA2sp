#pragma once

#include <CTriggerEvent.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerEventExt : public CTriggerEvent
{
public:

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerEventExt() {};
	~CTriggerEventExt() {};

	void OnBNCloneEventClicked();

private:

};