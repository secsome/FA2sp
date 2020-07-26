#pragma once

#include <CScriptTypes.h>
#include "../FA2Expand.h"

class NOVTABLE CScriptTypesExt : public CScriptTypes
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CScriptTypes* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CScriptTypesExt() {};
	~CScriptTypesExt() {};

private:

};