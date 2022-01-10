#pragma once

#include <CFinalSunApp.h>

#include <vector>
#include <string>

class NOVTABLE CFinalSunAppExt : public CFinalSunApp
{
public:
    static CFinalSunAppExt* GetInstance();

    BOOL InitInstanceExt();

    static std::vector<std::string> RecentFilesExt;
};