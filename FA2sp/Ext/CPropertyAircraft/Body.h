#pragma once

#include <CPropertyAircraft.h>
#include "../FA2Expand.h"

class NOVTABLE CPropertyAircraftExt : public CPropertyAircraft
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CPropertyAircraft* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CPropertyAircraftExt() {};
	~CPropertyAircraftExt() {};

private:

};