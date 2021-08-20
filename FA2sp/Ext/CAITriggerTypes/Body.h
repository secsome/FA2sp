#pragma once

#include <CAITriggerTypes.h>
#include "../FA2Expand.h"

class NOVTABLE CAITriggerTypesExt : public CAITriggerTypes
{
public:
	static void ProgramStartupInit();

	//
	// Ext Functions
	//
	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	CAITriggerTypesExt() {};
	~CAITriggerTypesExt() {};

	void OnBNCloneAITriggerClicked();
private:

};