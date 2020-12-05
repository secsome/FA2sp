#include <CINI.h>
#include <vector>
#include "../../FA2sp.h"

using std::vector;

static int LastReadIndex = -1;
static vector<INIClass*> LoadedINIs;
static vector<char*> LoadedINIFiles;

class FA2CMainWnd : FA2CWnd
{
public:
    void _47FFB0_loadTSINI(LPCSTR pFileName, INIClass* pINIFile, BOOL bAllowOverwrite)
    {
        JMP_THIS(0x47FFB0);
    }
};

static FA2CMainWnd* LoadingPtr = nullptr;

DEFINE_HOOK(47FFB0, INIClass_LoadTSINI_IncludeSupport_1, 7)
{
    //return 0;
    if (ExtConfigs::AllowIncludes)
    {
        GET(FA2CMainWnd*, LoadingPtr, ECX);
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
                    LoadingPtr->_47FFB0_loadTSINI(
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