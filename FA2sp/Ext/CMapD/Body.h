#pragma once

#include <CMapD.h>
#include "../FA2Expand.h"

class NOVTABLE CMapDExt : public CMapD
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CMapD* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CMapDExt() {};
	~CMapDExt() {};

private:

};