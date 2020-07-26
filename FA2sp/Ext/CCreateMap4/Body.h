#pragma once

#include <CCreateMap4.h>
#include "../FA2Expand.h"

class NOVTABLE CCreateMap4Ext : public CCreateMap4
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCreateMap4* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CCreateMap4Ext() {};
	~CCreateMap4Ext() {};

private:

};