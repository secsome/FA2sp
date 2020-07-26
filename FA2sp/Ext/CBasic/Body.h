#pragma once

#include <CBasic.h>
#include "../FA2Expand.h"

class NOVTABLE CBasicExt : public CBasic
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CBasic* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CBasicExt() {};
	~CBasicExt() {};

private:

};