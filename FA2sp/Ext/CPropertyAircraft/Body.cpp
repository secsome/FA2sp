#include "Body.h"

#include "../CFinalSunDlg/Body.h"

void CPropertyAircraftExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x591698, &CPropertyAircraftExt::PreTranslateMessageExt);
}

BOOL CPropertyAircraftExt::PreTranslateMessageExt(MSG* pMsg)
{
#define DECLARE_BST(id) \
if(pMsg->hwnd == this->GetDlgItem(id)->GetSafeHwnd()) \
{ \
	bool tmp = ::SendMessage(::GetDlgItem(*this, id), BM_GETCHECK, 0, 0) == BST_CHECKED; \
	::SendMessage(::GetDlgItem(*this, id), BM_SETCHECK, tmp ? BST_UNCHECKED : BST_CHECKED, 0); \
	ObjectBrowserControlExt::AircraftBrushBools[id-1300] = tmp == false; \
}
	if (pMsg->message == WM_LBUTTONUP)
	{
		DECLARE_BST(1300)
	else DECLARE_BST(1301)
	else DECLARE_BST(1302)
	else DECLARE_BST(1303)
	else DECLARE_BST(1304)
	else DECLARE_BST(1305)
	else DECLARE_BST(1306)
	else DECLARE_BST(1307)
	else DECLARE_BST(1308)
	}

#undef DECLARE_BST

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}