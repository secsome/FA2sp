#pragma once

#include <CSingleplayerSettings.h>
#include "../FA2Expand.h"

class NOVTABLE CSingleplayerSettingsExt : public CSingleplayerSettings
{
public:
	static void ProgramStartupInit();
	
private:
	BOOL PreTranslateMessageExt(MSG* pMsg);
	//BOOL OnCommandExt(WPARAM wParam, LPARAM lParam);

private:

};