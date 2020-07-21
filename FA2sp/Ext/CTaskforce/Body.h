#pragma once

#include "../FA2Expand.h"
#include <CTaskforce.h>

class NOVTABLE CTaskForceExt : public CTaskForce
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTaskForce* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CTaskForceExt() {};
	~CTaskForceExt() {};

private:

};