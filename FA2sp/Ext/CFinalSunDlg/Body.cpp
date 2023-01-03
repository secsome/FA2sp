#include "Body.h"

#include "../../FA2sp.h"
#include "../CIsoView/Body.h"
#include "../CFinalSunApp/Body.h"

#include <CLoading.h>
#include "../../Miscs/Palettes.h"

int CFinalSunDlgExt::CurrentLighting = 31000;

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
	auto SetLayerStatus = [this, &hMenu](int id, bool& param)
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

	auto SetLightingStatus = [this, &hMenu](int id)
	{
		CheckMenuRadioItem(hMenu, 31000, 31003, id, MF_UNCHECKED);
		if (CFinalSunDlgExt::CurrentLighting != id)
		{
			CFinalSunDlgExt::CurrentLighting = id;

			PalettesManager::ManualReloadTMP = true;
			PalettesManager::CacheAndTintCurrentIso();
			CLoading::Instance->FreeTMPs();
			CLoading::Instance->InitTMPs();
			PalettesManager::RestoreCurrentIso();
			PalettesManager::ManualReloadTMP = false;

			this->MyViewFrame.RedrawWindow(nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
		}
	};

	switch (wmID)
	{
	case 30000:
		SetLayerStatus(30000, CIsoViewExt::DrawStructures);
		return TRUE;
	case 30001:
		SetLayerStatus(30001, CIsoViewExt::DrawInfantries);
		return TRUE;
	case 30002:
		SetLayerStatus(30002, CIsoViewExt::DrawUnits);
		return TRUE;
	case 30003:
		SetLayerStatus(30003, CIsoViewExt::DrawAircrafts);
		return TRUE;
	case 30004:
		SetLayerStatus(30004, CIsoViewExt::DrawBasenodes);
		return TRUE;
	case 30005:
		SetLayerStatus(30005, CIsoViewExt::DrawWaypoints);
		return TRUE;
	case 30006:
		SetLayerStatus(30006, CIsoViewExt::DrawCelltags);
		return TRUE;
	case 30007:
		SetLayerStatus(30007, CIsoViewExt::DrawMoneyOnMap);
		return TRUE;
	case 30008:
		SetLayerStatus(30008, CIsoViewExt::DrawOverlays);
		return TRUE;
	case 30009:
		SetLayerStatus(30009, CIsoViewExt::DrawTerrains);
		return TRUE;
	case 30010:
		SetLayerStatus(30010, CIsoViewExt::DrawSmudges);
		return TRUE;
	case 30011:
		SetLayerStatus(30011, CIsoViewExt::DrawTubes);
		return TRUE;
	case 30012:
		SetLayerStatus(30012, CIsoViewExt::DrawBounds);
		return TRUE;
	case 31000:
	case 31001:
	case 31002:
	case 31003:
		SetLightingStatus(wmID);
		break;
	case 32000:
	case 32001:
	case 32002:
	case 32003:
	{
		HMENU hMenu = *this->GetMenu();
		if (GetMenuState(hMenu, wmID, MF_BYCOMMAND) & MF_CHECKED)
		{
			// set to false
			CIsoViewExt::AutoPropertyBrush[wmID - 32000] = false;
			CheckMenuItem(hMenu, wmID, MF_UNCHECKED);
		}
		else
		{
			// set to true
			CIsoViewExt::AutoPropertyBrush[wmID - 32000] = true;
			CheckMenuItem(hMenu, wmID, MF_CHECKED);
		}
		break;
	}
	default:
		break;
	}

	if (wmID >= 40140 && wmID < 40149)
	{
		auto& file = CFinalSunAppExt::RecentFilesExt[wmID - 40140];
		if (CLoading::IsFileExists(file.c_str()))
			this->LoadMap(file.c_str());
	}

	return this->ppmfc::CDialog::OnCommand(wParam, lParam);
}

BOOL CFinalSunDlgExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_INITDIALOG:
		;
		///*SetWindowTheme(*this, L"DarkMode_Explorer", NULL);*/
	}
	return ppmfc::CDialog::PreTranslateMessage(pMsg);
}