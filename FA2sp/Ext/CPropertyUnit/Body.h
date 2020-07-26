#pragma once

#include <CPropertyUnit.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyUnitExt : public CPropertyUnit
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CPropertyUnit* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CPropertyUnitExt() {};
	~CPropertyUnitExt() {};

private:

};