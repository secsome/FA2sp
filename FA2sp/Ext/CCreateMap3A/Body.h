#pragma once

#include <CCreateMap3A.h>
#include "../FA2Expand.h"

class NOVTABLE CCreateMap3AExt : public CCreateMap3A
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCreateMap3A* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CCreateMap3AExt() {};
	~CCreateMap3AExt() {};

private:

};