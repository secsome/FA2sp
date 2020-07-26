#pragma once

#include <CINIEditorImport.h>
#include "../FA2Expand.h"

class NOVTABLE CINIEditorImportExt : public CINIEditorImport
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CINIEditorImport* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CINIEditorImportExt() {};
	~CINIEditorImportExt() {};

private:

};