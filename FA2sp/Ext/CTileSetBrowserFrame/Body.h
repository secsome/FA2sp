#pragma once

#include <CTileSetBrowserFrame.h>
#include "../FA2Expand.h"

class NOVTABLE CTileSetBrowserFrameExt : public CTileSetBrowserFrame
{
public:

	static void ProgramStartupInit();

	enum class TabPage : int
	{
		TilesetBrowser = 0,
		TriggerSort = 1
	};

	//
	// Ext Functions
	//

	BOOL OnInitDialogExt();
	BOOL PreTranslateMessageExt(MSG* pMsg);
	BOOL OnNotifyExt(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	BOOL OnCommandExt(WPARAM wParam, LPARAM lParam);

	CTileSetBrowserFrameExt() {};
	~CTileSetBrowserFrameExt() {};

	// Functional Functions
	void OnBNTileManagerClicked();

	void InitTabControl();

private:

public:
	static HWND hTabCtrl;
};