#pragma once

#include <CCreateMap3B.h>
#include "../FA2Expand.h"

class NOVTABLE CCreateMap3BExt : public CCreateMap3B
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCreateMap3B* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CCreateMap3BExt() {};
	~CCreateMap3BExt() {};

private:

};