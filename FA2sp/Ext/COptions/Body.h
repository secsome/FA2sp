#pragma once

#include <COptions.h>
#include "../FA2Expand.h"

class NOVTABLE COptionsExt : public COptions
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static COptions* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	COptionsExt() {};
	~COptionsExt() {};

private:

};