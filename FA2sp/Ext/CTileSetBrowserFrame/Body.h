#pragma once

#include <CTileSetBrowserFrame.h>
#include "../FA2Expand.h"

class NOVTABLE CTileSetBrowserFrameExt : public CTileSetBrowserFrame
{
public:

	static void ProgramStartupInit();

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);

	CTileSetBrowserFrameExt() {};
	~CTileSetBrowserFrameExt() {};

	// Functional Functions
	void OnBNTileManagerClicked();

private:

};