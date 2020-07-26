#pragma once

#include <CLoading.h>
#include "../FA2Expand.h"

class NOVTABLE CLoadingExt : public CLoading
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CLoading* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CLoadingExt() {};
	~CLoadingExt() {};

private:

};