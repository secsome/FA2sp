#pragma once

#include <CSpecialFlags.h>
#include "../FA2Expand.h"

class NOVTABLE CSpecialFlagsExt : public CSpecialFlags
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CSpecialFlags* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CSpecialFlagsExt() {};
	~CSpecialFlagsExt() {};

private:

};