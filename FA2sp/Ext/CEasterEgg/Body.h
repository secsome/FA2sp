#pragma once

#include <CEasterEgg.h>
#include "../FA2Expand.h"

class NOVTABLE CEasterEggExt : public CEasterEgg
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CEasterEgg* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CEasterEggExt() {};
	~CEasterEggExt() {};

private:

};