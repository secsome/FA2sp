#include <CINI.h>
#include <vector>
#include <CMixFile.h>
#include <CLoading.h>

#include "../../Helpers/STDHelpers.h"
#include "../../FA2sp.h"

using std::vector;

static int LastReadIndex = -1;
static vector<INIClass*> LoadedINIs;
static vector<char*> LoadedINIFiles;

static CLoading* LoadingPtr = nullptr;

DEFINE_HOOK(4530F7, CLoading_ParseINI_PlusSupport, 8)
{
    if (ExtConfigs::AllowPlusEqual)
    {
        // length [0x1000]
        GET_STACK(INIClass*, pINI, STACK_OFFS(0x22FC, 0x22D0));
        LEA_STACK(char*, lpKey, STACK_OFFS(0x22FC, 0x200C));
        LEA_STACK(const char*, lpSection, STACK_OFFS(0x22FC, 0x210C));

        if (strcmp(lpKey, "+") == 0)
        {
            int attempt = 0;
            while (true)
            {
                sprintf_s(lpKey, 0x1000, "FA2sp%d", attempt);
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
        LoadingPtr = R->ECX<CLoading*>();
        GET_STACK(const char*, pFile, 0x4);
        GET_STACK(INIClass*, pINI, 0x8);

        LoadedINIs.push_back(pINI);
        LoadedINIFiles.push_back(_strdup(pFile));
    }
    return 0;
}

DEFINE_HOOK(480880, INIClass_LoadTSINI_IncludeSupport_2, 5)
{
    //return 0;
    if (ExtConfigs::AllowIncludes)
    {
        char buffer[0x80];
        if (LoadedINIs.size() == 0)
            return 0;
        INIClass* xINI = LoadedINIs.back();
        if (!xINI)
            return 0;

        const char* section = "#include";

        int len = xINI->GetKeyCount(section);
        for (int i = LastReadIndex; i < len; i = LastReadIndex)
        {
            const char* key = xINI->GetKeyName(section, i);
            ++LastReadIndex;
            buffer[0] = '\0';
            strcpy_s(buffer ,xINI->GetString(section, key, ""));
            if (buffer && strlen(buffer) > 0) {
                bool canLoad = true;
                for (size_t j = 0; j < LoadedINIFiles.size(); ++j) {
                    if (!strcmp(LoadedINIFiles[j], buffer)) {
                        canLoad = false;
                        break;
                    }
                }

                if (canLoad) {
                    Logger::Debug("Include Ext Loaded File: %s\n", buffer);
                    LoadingPtr->LoadTSINI(
                        buffer, xINI, TRUE
                    );
                }
            }
        }

        if (LoadedINIs.size() > 0)
            LoadedINIs.erase(LoadedINIs.end() - 1);
        if (!LoadedINIs.size()) {
            for (int j = LoadedINIFiles.size() - 1; j >= 0; --j) {
                if (char* ptr = LoadedINIFiles[j]) {
                    free(ptr);
                }
                LoadedINIFiles.erase(LoadedINIFiles.begin() + j);
            }
            LastReadIndex = -1;
        }

    }
    return 0;
}