#pragma once

#include <CFinalSunApp.h>

#include <vector>
#include <string>

class NOVTABLE CFinalSunAppExt : public CFinalSunApp
{
public:
    CFinalSunAppExt() = delete;

    static CFinalSunAppExt* GetInstance();

    BOOL InitInstanceExt();

    static std::vector<std::string> RecentFilesExt;
};