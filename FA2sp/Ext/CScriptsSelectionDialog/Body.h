#pragma once

#include <CScriptsSelectionDialog.h>
#include "../FA2Expand.h"

class NOVTABLE CScriptsSelectionDialogExt : public CScriptsSelectionDialog
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CScriptsSelectionDialog* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CScriptsSelectionDialogExt() = delete;
	~CScriptsSelectionDialogExt() {};

private:

};