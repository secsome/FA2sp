#pragma once

#include <CCreateMap2.h>
#include "../FA2Expand.h"

class NOVTABLE CCreateMap2Ext : public CCreateMap2
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCreateMap2* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CCreateMap2Ext() {};
	~CCreateMap2Ext() {};

private:

};