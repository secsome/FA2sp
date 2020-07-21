#pragma once

#include <CCreateMap1.h>
#include "../FA2Expand.h"

class NOVTABLE CCreateMap1Ext : public CCreateMap1
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCreateMap1* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CCreateMap1Ext() {};
	~CCreateMap1Ext() {};

private:

};