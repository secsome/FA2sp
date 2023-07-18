#include "Body.h"

#include <CFinalSunApp.h>
#include <CMixFile.h>
#include <CINI.h>

bool CLoadingExt::InitMixFilesFix()
{
	HasMdFile = true;

	// Load Extra Mixes
	{
		
		if (auto pSection = CINI::FAData->GetSection("ExtraMixes"))
		{
			std::map<int, ppmfc::CString> collector;

			for (const auto& [key, index] : pSection->GetIndices())
				collector[index] = key;

			ppmfc::CString path;

			for (const auto& [_, key] : collector)
			{
				if (CINI::FAData->GetBool("ExtraMixes", key))
					path = CFinalSunApp::Instance->ExePath;
				else
					path = CFinalSunApp::Instance->FilePath;
				path += "\\" + key;
				if (auto id = CMixFile::Open(path, 0))
				{
					Logger::Raw("[MixLoader][EXTRA] %04d - %s loaded.\n", id, path);
				}
				else
				{
					Logger::Raw("[MixLoader][EXTRA] %s failed!\n", path);
				}
			}
		}
	}

	ppmfc::CString Dir = CFinalSunApp::Instance->FilePath();
	Dir += "\\";
	auto LoadMixFile = [this, Dir](const char* Mix, int Parent = 0)
	{
		if (Parent)
		{
			int result = CMixFile::Open(Mix, Parent);
			if (result)
				Logger::Raw("[MixLoader] %04d - %s loaded.\n", result, Mix);
			else
				Logger::Raw("[MixLoader] %s failed!\n", Mix);
			return result;
		}
		else
		{
			ppmfc::CString FullPath = Dir + Mix;
			int result = CMixFile::Open(FullPath, 0);
			if (result)
			{
				Logger::Raw("[MixLoader] %04d - %s loaded.\n", result, FullPath);
				return result;
			}
			if (int nMix = SearchFile(Mix))
			{
				result = CMixFile::Open(Mix, nMix);
				if (result)
					Logger::Raw("[MixLoader] %04d - %s loaded.\n", result, Mix);
				else
					Logger::Raw("[MixLoader] %s failed!\n", Mix);
				return result;
			}
			Logger::Raw("[MixLoader] %s failed!\n", Mix);
			return result;
		}
	};
	auto SetMixFile = [LoadMixFile](const char* Mix, int& value)
	{
		value = LoadMixFile(Mix);
		return value;
	};

	// Init_Bootstrap_Mixfiles
	ppmfc::CString format = "EXPAND" + CINI::FAData->GetString("Filenames", "MixExtension", "MD") + "%02d.MIX";
	for (int i = 99; i >= 0; --i)
	{
		ppmfc::CString filename; 
		filename.Format(format, i);
		LoadMixFile(filename);
	}

	if (!LoadMixFile("RA2MD.MIX"))		return false;
	if (!LoadMixFile("RA2.MIX"))		return false;
	if (!LoadMixFile("CACHEMD.MIX"))	return false;
	if (!LoadMixFile("CACHE.MIX"))		return false;
	if (!LoadMixFile("LOCALMD.MIX"))	return false;
	if (!LoadMixFile("LOCAL.MIX"))		return false;

	// Init_Expansion_Mixfiles
	// ECACHE and ELOCAL
	WIN32_FIND_DATA fd;
	HANDLE hf = FindFirstFile(Dir + "ECACHE*.MIX", &fd);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fd.dwFileAttributes & (FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN))
				continue;
			LoadMixFile(fd.cFileName);
		} while (FindNextFile(hf, &fd));
		FindClose(hf);
	}
	hf = FindFirstFile(Dir + "ELOCAL*.MIX", &fd);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fd.dwFileAttributes & (FILE_ATTRIBUTE_TEMPORARY | FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN))
				continue;
			LoadMixFile(fd.cFileName);
		} while (FindNextFile(hf, &fd));
		FindClose(hf);
	}

	// Init_Secondary_Mixfiles
	if (!LoadMixFile("CONQMD.MIX"))		return false;
	if (!LoadMixFile("GENERMD.MIX"))	return false;
	if (!LoadMixFile("GENERIC.MIX"))	return false;
	if (!LoadMixFile("ISOGENMD.MIX"))	return false;
	if (!LoadMixFile("ISOGEN.MIX"))		return false;
	if (!LoadMixFile("CONQUER.MIX"))	return false;

	// Init_Theaters
	LoadMixFile("TEMPERAT.MIX");
	LoadMixFile("ISOTEMP.MIX");
	LoadMixFile("ISOTEMMD.MIX");
	LoadMixFile("TEM.MIX");
	LoadMixFile("TEMPERATMD.MIX");

	LoadMixFile("SNOW.MIX");
	LoadMixFile("ISOSNOW.MIX");
	LoadMixFile("ISOSNO.MIX");
	LoadMixFile("ISOSNOMD.MIX");
	LoadMixFile("SNO.MIX");
	LoadMixFile("SNOWMD.MIX");

	LoadMixFile("URBAN.MIX");
	LoadMixFile("ISOURB.MIX");
	LoadMixFile("ISOURBMD.MIX");
	LoadMixFile("URB.MIX");
	LoadMixFile("URBANMD.MIX");

	LoadMixFile("DESERT.MIX");
	LoadMixFile("ISODES.MIX");
	LoadMixFile("ISODESMD.MIX");
	LoadMixFile("DES.MIX");
	LoadMixFile("DESERTMD.MIX");

	LoadMixFile("URBANN.MIX");
	LoadMixFile("ISOUBN.MIX");
	LoadMixFile("ISOUBNMD.MIX");
	LoadMixFile("UBN.MIX");
	LoadMixFile("URBANNMD.MIX");

	LoadMixFile("LUNAR.MIX");
	LoadMixFile("ISOLUN.MIX");
	LoadMixFile("ISOLUNMD.MIX");
	LoadMixFile("LUN.MIX");
	LoadMixFile("LUNARMD.MIX");

	if (LoadMixFile("MARBLE.MIX"))
		CFinalSunApp::Instance->MarbleLoaded = TRUE;
	else
	{
		ppmfc::CString FullPath = CFinalSunApp::ExePath();
		FullPath += "\\MARBLE.MIX";
		int result = CMixFile::Open(FullPath, 0);
		if (result)
		{
			Logger::Raw("[MixLoader] %04d - %s loaded.\n", result, FullPath);
			CFinalSunApp::Instance->MarbleLoaded = TRUE;
		}
		else
		{
			CFinalSunApp::Instance->MarbleLoaded = FALSE;
			::MessageBox(NULL, "Failed to load marble.mix! Framework mode won't be able to use!", "FA2sp", MB_OK | MB_ICONEXCLAMATION);
		}
	}

	return true;
}