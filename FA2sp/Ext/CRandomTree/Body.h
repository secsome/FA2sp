#pragma once

#include <CRandomTree.h>
#include "../FA2Expand.h"

class NOVTABLE CRandomTreeExt : public CRandomTree
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CRandomTree* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CRandomTreeExt() {};
	~CRandomTreeExt() {};

private:

};