#pragma once

#include <CSearchWaypoint.h>
#include "../FA2Expand.h"

class NOVTABLE CSearchWaypointExt : public CSearchWaypoint
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CSearchWaypoint* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CSearchWaypointExt() {};
	~CSearchWaypointExt() {};

private:

};