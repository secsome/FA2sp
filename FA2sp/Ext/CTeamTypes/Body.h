#pragma once

#include <CTeamTypes.h>
#include "../FA2Expand.h"

class NOVTABLE CTeamTypesExt : public CTeamTypes
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTeamTypes* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CTeamTypesExt() {};
	~CTeamTypesExt() {};

private:

};