#pragma once

#include <CMapScripts.h>
#include "../FA2Expand.h"

class NOVTABLE CMapScriptsExt : public CMapScripts
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CMapScripts* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CMapScriptsExt() {};
	~CMapScriptsExt() {};

private:

};