#pragma once

#include <CWndView.h>
#include "../FA2Expand.h"

class NOVTABLE CMinimapExt : public CWndView
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CMinimapExt() {};
	~CMinimapExt() {};

private:

};