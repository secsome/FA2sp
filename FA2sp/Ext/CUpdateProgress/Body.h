#pragma once

#include <CUpdateProgress.h>
#include "../FA2Expand.h"

class NOVTABLE CUpdateProgressExt : public CUpdateProgress
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CUpdateProgress* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CUpdateProgressExt() {};
	~CUpdateProgressExt() {};

private:

};