#include "Body.h"

#include "../CFinalSunDlg/Body.h"

void CPropertyBuildingExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x592388, &CPropertyBuildingExt::PreTranslateMessageExt);
}

BOOL CPropertyBuildingExt::PreTranslateMessageExt(MSG* pMsg)
{
#define DECLARE_BST(id) \
if(pMsg->hwnd == this->GetDlgItem(id)->GetSafeHwnd()) \
{ \
	bool tmp = ::SendMessage(::GetDlgItem(*this, id), BM_GETCHECK, 0, 0) == BST_CHECKED; \
	::SendMessage(::GetDlgItem(*this, id), BM_SETCHECK, tmp ? BST_UNCHECKED : BST_CHECKED, 0); \
	ObjectBrowserControlExt::BuildingBrushBools[id-1300] = tmp == false; \
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
	else DECLARE_BST(1309)
	else DECLARE_BST(1310)
	else DECLARE_BST(1311)
	else DECLARE_BST(1312)
	else DECLARE_BST(1313)
	}

#undef DECLARE_BST

	return this->FA2CDialog::PreTranslateMessage(pMsg);
}