#include <CINI.h>
#include <vector>
#include <map>
#include <CLoading.h>

#include "../Helpers/STDHelpers.h"
#include "../FA2sp.h"

using std::map;
using std::vector;

class INIIncludes
{
public:
    static int LastReadIndex;
    static vector<CINI*> LoadedINIs;
    static vector<char*> LoadedINIFiles;
    static map<ppmfc::CString, unsigned int> CurrentINIIdxHelper;
};

int INIIncludes::LastReadIndex = -1;
vector<CINI*> INIIncludes::LoadedINIs;
vector<char*> INIIncludes::LoadedINIFiles;
map<ppmfc::CString, unsigned int> INIIncludes::CurrentINIIdxHelper;

DEFINE_HOOK(4530F7, CLoading_ParseINI_PlusSupport, 8)
{
    if (ExtConfigs::AllowPlusEqual)
    {
        // length [0x1000]
        GET_STACK(CINI*, pINI, STACK_OFFS(0x22FC, 0x22D0));
        LEA_STACK(char*, lpKey, STACK_OFFS(0x22FC, 0x200C));
        LEA_STACK(const char*, lpSection, STACK_OFFS(0x22FC, 0x210C));

        if (strcmp(lpKey, "+") == 0)
        {
            unsigned int& attempt = INIIncludes::CurrentINIIdxHelper[lpSection];
            while (true)
            {
                sprintf_s(lpKey, 0x1000, "FA2sp%u", attempt);
                if (!pINI->KeyExists(lpSection, lpKey))
                    break;
                ++attempt;
                if (attempt >= 10000)
                {
                    sprintf_s(lpKey, 0x1000, "+");
                    break;
                }
            }
        }
    }
    return 0;
}

DEFINE_HOOK(47FFB0, CLoading_LoadTSINI_IncludeSupport_1, 7)
{
    //return 0;
    if (ExtConfigs::AllowIncludes)
    {
        GET_STACK(const char*, pFile, 0x4);
        GET_STACK(CINI*, pINI, 0x8);

        INIIncludes::LoadedINIs.push_back(pINI);
        INIIncludes::LoadedINIFiles.push_back(_strdup(pFile));
    }
    return 0;
}

DEFINE_HOOK(480880, INIClass_LoadTSINI_IncludeSupport_2, 5)
{
    //return 0;
    if (ExtConfigs::AllowIncludes)
    {
        char buffer[0x80];
        if (INIIncludes::LoadedINIs.size() == 0)
            return 0;
        CINI* xINI = INIIncludes::LoadedINIs.back();
        if (!xINI)
            return 0;

        const char* section = "#include";

        int len = xINI->GetKeyCount(section);
        for (int i = INIIncludes::LastReadIndex; i < len; i = INIIncludes::LastReadIndex)
        {
            const char* key = xINI->GetKeyName(section, i);
            ++INIIncludes::LastReadIndex;
            buffer[0] = '\0';
            strcpy_s(buffer ,xINI->GetString(section, key, ""));
            if (buffer && strlen(buffer) > 0) {
                bool canLoad = true;
                for (size_t j = 0; j < INIIncludes::LoadedINIFiles.size(); ++j) {
                    if (!strcmp(INIIncludes::LoadedINIFiles[j], buffer)) {
                        canLoad = false;
                        break;
                    }
                }

                if (canLoad) {
                    Logger::Debug("Include Ext Loaded File: %s\n", buffer);
                    CLoading::Instance->LoadTSINI(
                        buffer, xINI, TRUE
                    );
                }
            }
        }

        if (INIIncludes::LoadedINIs.size() > 0)
            INIIncludes::LoadedINIs.erase(INIIncludes::LoadedINIs.end() - 1);
        if (!INIIncludes::LoadedINIs.size()) {
            for (int j = INIIncludes::LoadedINIFiles.size() - 1; j >= 0; --j) {
                if (char* ptr = INIIncludes::LoadedINIFiles[j]) {
                    free(ptr);
                    INIIncludes::CurrentINIIdxHelper.clear();
                }
                INIIncludes::LoadedINIFiles.erase(INIIncludes::LoadedINIFiles.begin() + j);
            }
            INIIncludes::LastReadIndex = -1;
        }

    }
    return 0;
}