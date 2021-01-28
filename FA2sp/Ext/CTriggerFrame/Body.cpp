#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerFrameExt::ProgramStartupInit()
{
	auto addr2 = &CTriggerFrameExt::OnInitDialogExt;
	RunTime::ResetMemoryContentAt(0x597BC4, &addr2, 4);
}

BOOL CTriggerFrameExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerFrame::OnInitDialog();
	if (!ret)
		return FALSE;

	auto TranslateDlgItem = [this](int nID, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			this->SetDlgItemText(nID, buffer);
	};

	auto TranslateCItem = [](CWnd* pWnd, const char* lpKey)
	{
		CString buffer;
		if (Translations::GetTranslationItem(lpKey, buffer))
			pWnd->SetWindowText(buffer);
	};

	TranslateCItem(this, "TriggerFrameTitle");

	TranslateDlgItem(50300, "TriggerFrameSelectedTrigger");

	TranslateDlgItem(1383, "TriggerFrameNew");
	TranslateDlgItem(1161, "TriggerFrameDel");
	TranslateDlgItem(1162, "TriggerFramePlace");
	TranslateDlgItem(1163, "TriggerFrameClone");

	return TRUE;
}

BOOL CTriggerFrameExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

DEFINE_HOOK(4CEC40, ASDUGVJBHASBDIHU, 7)
{
	Logger::Debug("ASGDVJHBAS\n");
	return 0;
}