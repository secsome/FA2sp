#pragma once

#include <CTriggerAction.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerActionExt : public CTriggerAction
{
public:

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerActionExt() {};
	~CTriggerActionExt() {};

	void OnBNCloneActionClicked();

	static int nCurrentParamCode;

private:

};