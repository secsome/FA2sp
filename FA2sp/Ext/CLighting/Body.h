#pragma once

#include <CLighting.h>
#include "../FA2Expand.h"

class NOVTABLE CLightingExt : public CLighting
{
public:
	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	void Translate();

	CLightingExt() {};
	~CLightingExt() {};

private:

};