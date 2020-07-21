#pragma once

#include <CMMX.h>
#include "../FA2Expand.h"

class NOVTABLE CMMXExt : public CMMX
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CMMX* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CMMXExt() {};
	~CMMXExt() {};

private:

};