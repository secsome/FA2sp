#include <Helpers/Macro.h>
#include <FAMemory.h>

#include <CLoading.h>

#include <fstream>

#ifndef NDEBUG
DEFINE_HOOK(438DB0, CFinalSunDlg_MapTools_SearchWaypoint_DEBUGDumpFile, 6)
{
	constexpr const char* Filename = "snowmo.ini";

	DWORD size;
	auto buffer = CLoading::Instance->ReadWholeFile(Filename, &size);

	std::ofstream fout;
	fout.open(Filename, std::ios::out | std::ios::binary);
	fout.write((const char*)buffer, size);
	fout.close();
	GameDelete(buffer);
	return 0x438E4E;
}
#endif