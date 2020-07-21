#pragma once

#include <CPropertyInfantry.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyInfantryExt : public CPropertyInfantry
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CPropertyInfantry* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CPropertyInfantryExt() {};
	~CPropertyInfantryExt() {};

private:

};