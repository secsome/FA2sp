#pragma once

#include <CCredits.h>
#include "../FA2Expand.h"

class NOVTABLE CCreditsExt : public CCredits
{
public:
	typedef BOOL(*FuncT_PTM)(MSG* pMsg);

	static CCredits* Instance;

	//hook function to replace in virtual function map
	BOOL PreTranslateMessageExt(MSG* pMsg);


	static void ProgramStartupInit();

	CCreditsExt() {};
	~CCreditsExt() {};

private:

};