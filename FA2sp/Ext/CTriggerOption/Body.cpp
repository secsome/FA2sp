#include "Body.h"

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerOptionExt::ProgramStartupInit()
{
	// Name Update, EN_CHANGE -> EN_KILLFOCUS, reduce lag
	// RunTime::ResetMemoryContentAt(0x597D60 + 0x4, &RunTime::Messages::EDIT_KILLFOCUS, 4);

	RunTime::ResetMemoryContentAt(0x597F24, &CTriggerOptionExt::OnInitDialogExt);
	// RunTime::ResetMemoryContentAt(0x597EF8, &CTriggerOptionExt::PreTranslateMessageExt);
}

BOOL CTriggerOptionExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerOption::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, 50400, "TriggerOptionType");
	Translations::TranslateItem(this, 50401, "TriggerOptionName");
	Translations::TranslateItem(this, 50402, "TriggerOptionHouse");
	Translations::TranslateItem(this, 50403, "TriggerOptionAttached");
	Translations::TranslateItem(this, 50404, "TriggerOptionDisabledDesc");
	
	Translations::TranslateItem(this, 1412, "TriggerOptionDisabled");
	Translations::TranslateItem(this, 1424, "TriggerOptionEasy");
	Translations::TranslateItem(this, 1425, "TriggerOptionMedium");
	Translations::TranslateItem(this, 1426, "TriggerOptionHard");

	return TRUE;
}

BOOL CTriggerOptionExt::PreTranslateMessageExt(MSG* pMsg)
{
	// Original tooltip
	this->CTTCHouse.RelayEvent(pMsg);

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (::GetDlgCtrlID(pMsg->hwnd) == 1010)
		{
			this->OnETNameEdited();
			return TRUE;
		}
	}

	return this->ppmfc::CDialog::PreTranslateMessage(pMsg);
}