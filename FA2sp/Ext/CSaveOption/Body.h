#pragma once

#include <CSaveOption.h>
#include "../FA2Expand.h"

class NOVTABLE CSaveOptionExt : public CSaveOption
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CSaveOption* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CSaveOptionExt() {};
	~CSaveOptionExt() {};

private:

};