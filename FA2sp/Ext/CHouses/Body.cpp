#include "Body.h"

#include "../../Helpers/STDHelpers.h"

#include "../../ExtraWindow/CAllieEditor/CAllieEditor.h"

void CHousesExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x593DE8, &CHousesExt::PreTranslateMessageExt);

	//RunTime::ResetMemoryContentAt(0x593C80 + 0x4, &RunTime::Messages::COMBOBOX_KILLFOCUS, 4);
}

void CHousesExt::UpdateComboboxContents()
{
	this->CCBColor.DeleteAllStrings();
	this->CCBCountry.DeleteAllStrings();
	this->CCBHouses.DeleteAllStrings();
	this->CCBHumanHouse.DeleteAllStrings();

	auto& doc = CINI::CurrentDocument();
	
}

BOOL CHousesExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {
	case WM_LBUTTONUP:
	{
		if (pMsg->hwnd == this->GetDlgItem(1145)->m_hWnd)
			CAllieEditor::Create();
	}
	default:
		break;
	}
	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}
