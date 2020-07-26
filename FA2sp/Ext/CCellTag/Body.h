#pragma once

#include <CCellTag.h>
#include "../FA2Expand.h"

class NOVTABLE CCellTagExt : public CCellTag
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCellTag* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CCellTagExt() {};
	~CCellTagExt() {};

private:

};