#include "Body.h"

#include "../../FA2sp.h"

void CFinalSunDlgExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x5937E8, &CFinalSunDlgExt::PreTranslateMessageExt);

}

BOOL CFinalSunDlgExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_INITDIALOG:
		;
		///*SetWindowTheme(*this, L"DarkMode_Explorer", NULL);*/
	}
	return FA2CDialog::PreTranslateMessage(pMsg);
}