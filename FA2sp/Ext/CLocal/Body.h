#pragma once

#include <CLocal.h>
#include "../FA2Expand.h"

class NOVTABLE CLocalExt : public CLocal
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CLocal* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CLocalExt() {};
	~CLocalExt() {};

private:

};