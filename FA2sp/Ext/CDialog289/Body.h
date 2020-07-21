#pragma once

#include <CDialog289.h>
#include "../FA2Expand.h"

class NOVTABLE CDialog289Ext : public CDialog289
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CDialog289* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CDialog289Ext() {};
	~CDialog289Ext() {};

private:

};