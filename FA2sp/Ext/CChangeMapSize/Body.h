#pragma once

#include <CChangeMapSize.h>
#include "../FA2Expand.h"

class NOVTABLE CChangeMapSizeExt : public CChangeMapSize
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CChangeMapSize* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CChangeMapSizeExt() {};
	~CChangeMapSizeExt() {};

private:

};