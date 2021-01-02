#pragma once

#include <CTileSetBrowserView.h>
#include "../FA2Expand.h"

class NOVTABLE CTileSetBrowserViewExt : public CTileSetBrowserView
{
public:

	static void ProgramStartupInit();

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	CTileSetBrowserViewExt() {};
	~CTileSetBrowserViewExt() {};

	// Functional Functions
	void OnBNTileManagerClicked();

private:

};