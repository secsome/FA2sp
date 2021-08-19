#include <Helpers/Macro.h>

#include <CINI.h>
#include <CFinalSunDlg.h>
#include <CMapData.h>
#include <GlobalVars.h>

#include "../FA2sp.h"
#include "../FA2sp.Constants.h"

#include <map>
#include <sstream>

// FA2 SaveMap is almost O(N^4), who wrote that?
DEFINE_HOOK(428D97, CFinalSunDlg_SaveMap, 7)
{
    if (ExtConfigs::SaveMap)
    {
        GET(INIClass*, pINI, EAX);
        GET_STACK(CFinalSunDlg*, pThis, STACK_OFFS(0x3F4, 0x36C));
        REF_STACK(ppmfc::CString, filepath, STACK_OFFS(0x3F4, -0x4));
        LEA_STACK(ppmfc::CString*, pPath, STACK_OFFS(0x3F4, 0x360));

        ppmfc::CString path = "TmpMap.map";

        pThis->MyViewFrame.StatusBar.SetWindowText("Saving...");
        pThis->MyViewFrame.StatusBar.UpdateWindow();

        DeleteFile(filepath);
        CloseHandle(
            CreateFile(filepath, GENERIC_WRITE, NULL, nullptr, TRUNCATE_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN | FILE_ATTRIBUTE_NORMAL, NULL)
        );
        auto hFile = CreateFile(filepath, GENERIC_WRITE, NULL, nullptr, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN | FILE_ATTRIBUTE_NORMAL, NULL);

        std::stringstream ss;
        ss <<
            "; Map created with FinalAlert 2(tm) Mission Editor\n"
            "; Get it at http://www.westwood.com\n"
            "; note that all comments were truncated\n"
            "\n"
            "; This FA2 uses FA2sp created by secsome\n"
            "; Get the lastest dll at https://github.com/secsome/FA2sp\n"
            "; Current version : ";
        ss << PRODUCT_STR;
        ss << "\n\n";

        for (auto& section : pINI->Dict)
        {
            ss << "[";
            ss << section.first;
            ss << "]\n";
            for (auto& pair : section.second.EntitiesDictionary)
            {
                ss << pair.first;
                ss << "=";
                ss << pair.second;
                ss << "\n";
            }
            ss << "\n";
        }

        WriteFile(hFile, ss.str().c_str(), ss.str().length(), nullptr, nullptr);
        CloseHandle(hFile);

        new(pPath) ppmfc::CString(path);

        return 0x42A859;
    }

    return 0;
}

DEFINE_HOOK(42B30F, CFinalSunDlg_SaveMap_SkipMapDTOR, 7)
{
    return ExtConfigs::SaveMap ? 0x42B323 : 0;
}

DEFINE_HOOK(42B2AF, CFinalSunDlg_SaveMap_SkipDeleteFile, 7)
{
    return ExtConfigs::SaveMap ? 0x42B2C2 : 0;
}

DEFINE_HOOK(42A8F5, CFinalSunDlg_SaveMap_ReplaceCopyFile, 7)
{
    if (!ExtConfigs::SaveMap)
        return 0;

    REF_STACK(ppmfc::CString, filepath, STACK_OFFS(0x3F4, -0x4));

    HANDLE hFile =
        CreateFile(filepath, GENERIC_READ, NULL, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return 0x42A92D;
    }
    return 0x42A911;
}

class SaveMapExt
{
private:
    static UINT_PTR Timer;
public:
    static bool IsAutoSaving;

    static void ResetTimer()
    {
        StopTimer();
        if (ExtConfigs::SaveMap_AutoSave_Interval >= 30)
        {
            Timer = SetTimer(GlobalVars::Dialogs::CFinalSunDlg->m_hWnd,
                NULL, 1000 * ExtConfigs::SaveMap_AutoSave_Interval, SaveMapCallback);
        }
    }

    static void StopTimer()
    {
        if (Timer != NULL)
        {
            KillTimer(GlobalVars::Dialogs::CFinalSunDlg->m_hWnd, Timer);
            Timer = NULL;
        }
    }

    static void RemoveEarlySaves()
    {
        if (ExtConfigs::SaveMap_AutoSave_MaxCount != -1)
        {
            struct FileTimeComparator
            {
                bool operator()(const FILETIME& a, const FILETIME& b) const { return CompareFileTime(&a, &b) == -1; }
            };

            std::map<FILETIME, ppmfc::CString, FileTimeComparator> m;

            ppmfc::CString buffer = GlobalVars::ExePath();
            buffer += "\\AutoSaves\\autosave-*.map";
            WIN32_FIND_DATA Data;
            auto hFindData = FindFirstFile(buffer, &Data);
            while (hFindData != INVALID_HANDLE_VALUE)
            {
                m[Data.ftLastWriteTime] = Data.cFileName;
                if (!FindNextFile(hFindData, &Data))
                    break;
            }

            int count = m.size() - ExtConfigs::SaveMap_AutoSave_MaxCount;
            if (count <= 0)    
                return;

            auto& itr = m.begin();
            while (count != 0)
            {
                buffer.Format("%s\\AutoSaves\\%s", GlobalVars::ExePath(), itr->second);
                DeleteFile(buffer);
                ++itr;
                --count;
            }
        }
    }

    static void CALLBACK SaveMapCallback(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
    {
        if (!GlobalVars::CMapData->MapWidthPlusHeight || !GlobalVars::CMapData->FieldDataAllocated)
        {
            StopTimer();
            return;
        }

        SYSTEMTIME time;
        GetLocalTime(&time);

        ppmfc::CString buffer = GlobalVars::ExePath();
        buffer += "\\AutoSaves";
        CreateDirectory(buffer, nullptr);

        buffer.Format("%s\\AutoSaves\\autosave-%04d%02d%02d-%02d%02d%02d-%03d.map", 
            GlobalVars::ExePath(),
            time.wYear, time.wMonth, time.wDay, 
            time.wHour, time.wMinute, time.wSecond, 
            time.wMilliseconds
        );
        
        IsAutoSaving = true;
        GlobalVars::Dialogs::CFinalSunDlg->SaveMap(buffer);
        IsAutoSaving = false;

        RemoveEarlySaves();
    }
};

bool SaveMapExt::IsAutoSaving = false;
UINT_PTR SaveMapExt::Timer = NULL;

DEFINE_HOOK(426E50, CFinalSunDlg_SaveMap_AutoSave_StopTimer, 7)
{
    SaveMapExt::StopTimer();
    return 0;
}

DEFINE_HOOK(42B3AC, CFinalSunDlg_SaveMap_AutoSave_ResetTimer, 7)
{
    SaveMapExt::ResetTimer();
    return 0;
}

DEFINE_HOOK(427949, CFinalSunDlg_SaveMap_AutoSave_SkipDialog, A)
{
    return SaveMapExt::IsAutoSaving ? 0x428CF6 : 0;
}

DEFINE_HOOK(42B294, CFinalSunDlg_SaveMap_AutoSave_SkipEditFilesMenu, 8)
{
    return SaveMapExt::IsAutoSaving ? 0x42B2AF : 0;
}