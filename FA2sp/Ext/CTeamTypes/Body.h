#pragma once

#include <CTeamTypes.h>
#include "../FA2Expand.h"

class NOVTABLE CTeamTypesExt : public CTeamTypes
{
public:

	static void ProgramStartupInit();

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	CTeamTypesExt() {};
	~CTeamTypesExt() {};

	// Functional Functions
	void OnBNCloneClicked();

private:

};