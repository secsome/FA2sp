#include "Body.h"

#include "../../FA2sp.h"
#include "../CIsoView/Body.h"


void CFinalSunDlgExt::ProgramStartupInit()
{
	// RunTime::ResetMemoryContentAt(0x5937E8, &CFinalSunDlgExt::PreTranslateMessageExt);
	RunTime::ResetMemoryContentAt(0x5937D0, &CFinalSunDlgExt::OnCommandExt);
}

BOOL CFinalSunDlgExt::OnCommandExt(WPARAM wParam, LPARAM lParam)
{
	WORD wmID = LOWORD(wParam);
	WORD wmMsg = HIWORD(wParam);

	HMENU hMenu = *this->GetMenu();
	auto SetMenuStatus = [this, &hMenu](int id, bool& param)
	{
		if (GetMenuState(hMenu, id, MF_BYCOMMAND) & MF_CHECKED)
		{
			param = false;
			CheckMenuItem(hMenu, id, MF_UNCHECKED);
		}
		else
		{
			param = true;
			CheckMenuItem(hMenu, id, MF_CHECKED);
		}
		this->MyViewFrame.RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
	};

	switch (wmID)
	{
	case 30000:
		SetMenuStatus(30000, CIsoViewExt::DrawStructures);
		return TRUE;
	case 30001:
		SetMenuStatus(30001, CIsoViewExt::DrawInfantries);
		return TRUE;
	case 30002:
		SetMenuStatus(30002, CIsoViewExt::DrawUnits);
		return TRUE;
	case 30003:
		SetMenuStatus(30003, CIsoViewExt::DrawAircrafts);
		return TRUE;
	case 30004:
		SetMenuStatus(30004, CIsoViewExt::DrawBasenodes);
		return TRUE;
	case 30005:
		SetMenuStatus(30005, CIsoViewExt::DrawWaypoints);
		return TRUE;
	case 30006:
		SetMenuStatus(30006, CIsoViewExt::DrawCelltags);
		return TRUE;
	case 30007:
		SetMenuStatus(30007, CIsoViewExt::DrawMoneyOnMap);
		return TRUE;
	case 30008:
		SetMenuStatus(30008, CIsoViewExt::DrawOverlays);
		return TRUE;
	case 30009:
		SetMenuStatus(30009, CIsoViewExt::DrawTerrains);
		return TRUE;
	case 30010:
		SetMenuStatus(30010, CIsoViewExt::DrawSmudges);
		return TRUE;
	case 30011:
		SetMenuStatus(30011, CIsoViewExt::DrawTubes);
		return TRUE;
	case 30012:
		SetMenuStatus(30012, CIsoViewExt::DrawBounds);
		return TRUE;
	default:
		break;
	}

	return this->FA2CDialog::OnCommand(wParam, lParam);
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