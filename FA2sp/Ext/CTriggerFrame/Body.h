#pragma once

#include <CTriggerFrame.h>
#include "../FA2Expand.h"

class NOVTABLE CTriggerFrameExt : public CTriggerFrame
{
public:

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTriggerFrameExt() {};
	~CTriggerFrameExt() {};

private:

public:
	static bool CreateFromTriggerSort;
};