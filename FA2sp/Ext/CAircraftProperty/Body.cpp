#include "Body.h"

CAircraftProperty* CAircraftPropertyExt::Instance = nullptr;

void CAircraftPropertyExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591698, &CAircraftPropertyExt::PreTranslateMessageExt);
}

BOOL CAircraftPropertyExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}