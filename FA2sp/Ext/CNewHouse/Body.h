#pragma once

#include <CNewHouse.h>
#include "../FA2Expand.h"

class NOVTABLE CNewHouseExt : public CNewHouse
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CNewHouse* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CNewHouseExt() {};
	~CNewHouseExt() {};

private:

};