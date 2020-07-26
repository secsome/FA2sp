#pragma once

#include <CLoadingGraphics.h>
#include "../FA2Expand.h"

class NOVTABLE CLoadingGraphicsExt : public CLoadingGraphics
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CLoadingGraphics* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CLoadingGraphicsExt() {};
	~CLoadingGraphicsExt() {};

private:

};