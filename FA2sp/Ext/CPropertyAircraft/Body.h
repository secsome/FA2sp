#pragma once

#include <CAircraftProperty.h>
#include "../FA2Expand.h"

class NOVTABLE CAircraftPropertyExt : public CAircraftProperty
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CAircraftProperty* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CAircraftPropertyExt() {};
	~CAircraftPropertyExt() {};

private:

};