#pragma once

#include <CINIEditor.h>
#include "../FA2Expand.h"

class NOVTABLE CINIEditorExt : public CINIEditor
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CINIEditor* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageHook(MSG* pMsg);

	static void ProgramStartupInit();

	CINIEditorExt() {};
	~CINIEditorExt() {};

private:

};