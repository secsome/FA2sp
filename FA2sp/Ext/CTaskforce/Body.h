#pragma once

#include "../FA2Expand.h"
#include <CTaskforce.h>

class NOVTABLE CTaskForceExt : public CTaskForce
{
public:

	static void ProgramStartupInit();

	//
	// Ext Functions
	//
	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	CTaskForceExt() {};
	~CTaskForceExt() {};

	void OnBNCloneTaskforceClicked();

private:

};