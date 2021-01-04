#pragma once

#include <CPropertyBuilding.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyBuildingExt : public CPropertyBuilding
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CPropertyBuilding* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	// Ext Functions
	//BOOL OnInitDialogExt();

	static void ProgramStartupInit();

	CPropertyBuildingExt() {};
	~CPropertyBuildingExt() {};

private:

};