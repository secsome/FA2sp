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
	};

	switch (wmID)
	{
	case 30000:
		SetMenuStatus(30000, CIsoViewExt::DrawStructures);
		break;
	case 30001:
		SetMenuStatus(30001, CIsoViewExt::DrawInfantries);
		break;
	case 30002:
		SetMenuStatus(30002, CIsoViewExt::DrawUnits);
		break;
	case 30003:
		SetMenuStatus(30003, CIsoViewExt::DrawAircrafts);
		break;
	case 30004:
		SetMenuStatus(30004, CIsoViewExt::DrawBasenodes);
		break;
	case 30005:
		SetMenuStatus(30005, CIsoViewExt::DrawWaypoints);
		break;
	case 30006:
		SetMenuStatus(30006, CIsoViewExt::DrawCelltags);
		break;
	case 30007:
		SetMenuStatus(30007, CIsoViewExt::DrawMoneyOnMap);
		break;
	case 30008:
		SetMenuStatus(30008, CIsoViewExt::DrawOverlays);
		break;
	case 30009:
		SetMenuStatus(30009, CIsoViewExt::DrawTerrains);
		break;
	case 30010:
		SetMenuStatus(30010, CIsoViewExt::DrawSmudges);
		break;
	case 30011:
		SetMenuStatus(30011, CIsoViewExt::DrawTubes);
		break;
	case 30012:
		SetMenuStatus(30012, CIsoViewExt::DrawBounds);
		break;
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