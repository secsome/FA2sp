#pragma once

#include <CHouses.h>
#include "../FA2Expand.h"

class NOVTABLE CHousesExt : public CHouses
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CHouses* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);


	static void ProgramStartupInit();

	CHousesExt() {};
	~CHousesExt() {};

private:

};