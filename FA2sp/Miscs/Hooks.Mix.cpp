#include <Helpers/Macro.h>

DEFINE_HOOK(527F95, MixFile_Open_CheckTD, 7)
{
	return 0x527FBB;
}

DEFINE_HOOK(5281EE, MixFile_Open_CheckRAUnencrypted, 5)
{
	return 0x52823E;
}

DEFINE_HOOK(527F95, MixFile_Open_CheckRAEncrypted, 6)
{
	return 0x528124;
}

int extramix = 0;

#include "../FA2sp.h"
#include <CFinalSunApp.h>
#include <CMixFile.h>
#include <CLoading.h>

#include <set>

std::vector<int> ExtraMixes;

DEFINE_HOOK(48A1AD, CLoading_InitMixFiles_ExtraMix, 7)
{
	ExtraMixes.clear();

	if (auto pSection = CINI::FAData->GetSection("ExtraMixes"))
	{
		std::map<int, ppmfc::CString> collector;

		for (auto& pair : pSection->IndicesDictionary)
			collector[pair.second] = pair.first;

		ppmfc::CString path;

		for (auto& pair : collector)
		{
			if (CINI::FAData->GetBool("ExtraMixes", pair.second))
				path = CFinalSunApp::Instance->ExePath;
			else
				path = CFinalSunApp::Instance->FilePath;
			path += "\\" + pair.second;
			if (auto id = CMixFile::Open(path, 0))
				ExtraMixes.push_back(id);
		}
	}
	
	return 0;
}

DEFINE_HOOK(48A650, CLoading_SearchFile_ExtraMix, 6)
{
	GET_STACK(const char*, pName, 0x4);

	for (auto& id : ExtraMixes)
	{
		if (CMixFile::HasFile(pName, id))
		{
			R->EAX(id);
			return 0x48ABD8;
		}
	}

	return 0;
}