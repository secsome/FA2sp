#pragma once

#include <CSingleplayerSettings.h>
#include "../FA2Expand.h"

class NOVTABLE CSingleplayerSettingsExt : public CSingleplayerSettings
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CSingleplayerSettings* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CSingleplayerSettingsExt() {};
	~CSingleplayerSettingsExt() {};

private:

};