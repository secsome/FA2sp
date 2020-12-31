#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"

void CHousesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x593C80 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4);
}

void CHousesExt::UpdateComboboxContents()
{
	while (this->CCBColor.DeleteString(0) != -1);
	while (this->CCBCountry.DeleteString(0) != -1);
	while (this->CCBHouses.DeleteString(0) != -1);
	while (this->CCBHumanHouse.DeleteString(0) != -1);

	auto& doc = GlobalVars::INIFiles::CurrentDocument();
	
}

BOOL CHousesExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {
	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}
