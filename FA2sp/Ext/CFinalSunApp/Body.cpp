#include "Body.h"

#include <CFinalSunDlg.h>
#include <CINI.h>
#include <CLoading.h>

#include "../../FA2sp.h"

#pragma warning(disable : 6262)

std::vector<std::string> CFinalSunAppExt::RecentFilesExt;

CFinalSunAppExt* CFinalSunAppExt::GetInstance()
{
	return static_cast<CFinalSunAppExt*>(&CFinalSunApp::Instance.get());
}

BOOL CFinalSunAppExt::InitInstanceExt()
{
	this->AccTable = ::LoadAccelerators(static_cast<HINSTANCE>(FA2sp::hInstance), MAKEINTRESOURCE(0x81));

	HWND hDesktop = ::GetDesktopWindow();
	HDC hDC = ::GetDC(hDesktop);
	if (::GetDeviceCaps(hDC, BITSPIXEL) <= 8)
	{
		::MessageBox(
			NULL,
			"You currently only have 8 bit color mode enabled. "
			"FinalAlert 2(tm)will not work in 8 bit color mode. "
			"See readme.txt for further information!",
			"Error",
			MB_OK
		);
		exit(0);
	}
	
	std::string cmdline = this->m_lpCmdLine;
	CFinalSunDlg::SE2KMODE = FALSE; // We don't need SE2K stuff
	CFinalSunApp::MapPath[0] = '\0';

	std::string path;
	path = CFinalSunApp::ExePath + "\\FAData.ini";
	CINI::FAData->ClearAndLoad(path.c_str());

	FA2sp::ExtConfigsInitialize(); // ExtConfigs

	path = CFinalSunApp::ExePath + "\\FALanguage.ini";
	CINI::FALanguage->ClearAndLoad(path.c_str());
	// No need to validate falanguage I guess

	CINI ini;
	path = CFinalSunApp::ExePath + "\\FinalAlert.ini";
	ini.ClearAndLoad(path.c_str());
	if (
		!ini.KeyExists("TS", "Exe") || 
		!ini.KeyExists("FinalSun", "FileSearchLikeTS") || 
		!ini.KeyExists("FinalSun", "Language")
		)
	{
		this->FileSearchLikeTS = TRUE;
		*reinterpret_cast<int*>(0x7EE07C) = TRUE; // Settings::NoNeedForRestart
		this->GetDlg()->Settings();
		*reinterpret_cast<int*>(0x7EE07C) = FALSE;
	}
	else
	{
		this->InstallPath = ini.GetString("TS", "Exe");
		this->FileSearchLikeTS = ini.GetBool("FinalSun", "FileSearchLikeTS");
		this->Language = ini.GetString("FinalSun", "Language");
	}
	
	// No graphics, no need for them in fact
	this->NoAircraftGraphics = ini.GetBool("Graphics", "NoAircraftGraphics");
	this->NoVehicleGraphics = ini.GetBool("Graphics", "NoVehicleGraphics");
	this->NoBuildingGraphics = ini.GetBool("Graphics", "NoBuildingGraphics");
	this->NoInfantryGraphics = ini.GetBool("Graphics", "NoInfantryGraphics");
	this->NoTreeGraphics = ini.GetBool("Graphics", "NoTreeGraphics");
	this->NoSnowGraphics = ini.GetBool("Graphics", "NoSnowGraphics");
	this->NoTemperateGraphics = ini.GetBool("Graphics", "NoTemperateGraphics");
	this->NoBMPs = ini.GetBool("Graphics", "NoBMPs");
	this->NoOverlayGraphics = ini.GetBool("Graphics", "NoOverlayGraphics");

	// User interface
	this->DisableAutoShore = ini.GetBool("UserInterface", "DisableAutoShore");
	this->DisableAutoLat = ini.GetBool("UserInterface", "DisableAutoLat");
	this->NoSounds = ini.GetBool("UserInterface", "NoSounds");
	this->DisableSlopeCorrection = ini.GetBool("UserInterface", "DisableSlopeCorrection");
	this->ShowBuildingCells = ini.GetBool("UserInterface", "ShowBuildingCells");
	
	// recent files
	this->RecentFilesExt.resize(ExtConfigs::RecentFileLimit);
	for (size_t i = 0; i < this->RecentFilesExt.size(); ++i)
		this->RecentFilesExt[i] = ini.GetString("Files", std::format("{0:d}", i).c_str());

	if (this->NoTemperateGraphics && this->NoSnowGraphics)
	{
		::MessageBox(
			NULL,
			"You have turned off loading of both snow and temperate terrain in 'FinalAlert.ini'. "
			"At least one of these must be loaded. The application will now quit.",
			"Error",
			MB_OK);
		exit(0xFFFFFC2A);
	}

	// No easy mode
	this->EasyMode = FALSE;

	// Process file path
	FA2sp::Buffer = this->InstallPath;
	FA2sp::Buffer.SetAt(FA2sp::Buffer.ReverseFind('\\') + 1, '\0');
	strcpy_s(CFinalSunApp::FilePath, 260, FA2sp::Buffer);
	
	// Others
	CLoading loading(nullptr);
	this->Loading = &loading;
	
	CFinalSunDlg dlg(nullptr);
	this->m_pMainWnd = (CWnd*)&dlg;

	dlg.DoModal();

	return FALSE;
}