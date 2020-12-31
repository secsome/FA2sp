#pragma once

#include <CHouses.h>
#include "../FA2Expand.h"

class NOVTABLE CHousesExt : public CHouses
{
public:
	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	//
	// Ext Functions
	//

	void UpdateComboboxContents();

	static void ProgramStartupInit();

	CHousesExt() {};
	~CHousesExt() {};

private:

};