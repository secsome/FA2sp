#pragma once

#include <CTags.h>
#include "../FA2Expand.h"

class NOVTABLE CTagsExt : public CTags
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CTags* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	CTagsExt() {};
	~CTagsExt() {};

private:

};