#include "SaveMap.h"

#include <Helpers/Macro.h>

#include <CINI.h>
#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>
#include <CLoading.h>
#include <CMapData.h>

#include "../FA2sp.h"
#include "../FA2sp.Constants.h"

#include <algorithm>
#include <map>
#include <fstream>
#include <format>

DEFINE_HOOK(4D5505, CSaveOption_CTOR_DefaultValue, 0)
{
    int nValue = CMapData::Instance->IsMultiOnly() ? 
        ExtConfigs::SaveMap_DefaultPreviewOptionMP : 
        ExtConfigs::SaveMap_DefaultPreviewOptionSP
        ;

    R->EBX(std::clamp(nValue, 0, 2));
    
    return 0x4D550E;
}

// FA2 SaveMap is almost O(N^4), who wrote that?
DEFINE_HOOK(428D97, CFinalSunDlg_SaveMap, 7)
{
    GET(CINI*, pINI, EAX);
    GET_STACK(CFinalSunDlg*, pThis, STACK_OFFS(0x3F4, 0x36C));
    REF_STACK(ppmfc::CString, filepath, STACK_OFFS(0x3F4, -0x4));

    GET_STACK(int, previewOption, STACK_OFFS(0x3F4, 0x1AC));

    pThis->MyViewFrame.StatusBar.SetWindowText("Saving...");
    pThis->MyViewFrame.StatusBar.UpdateWindow();

    ppmfc::CString buffer;
    buffer.Format("%d", pINI->GetInteger("FA2spVersionControl", "Version") + 1);
    pINI->WriteString("FA2spVersionControl", "Version", buffer);

    Logger::Raw("SaveMap : Now removing empty sections and keys.\n");
    std::vector<ppmfc::CString> sectionsToRemove;
    for (auto& section_pair : pINI->Dict)
    {
        ppmfc::CString buffer;
        buffer = section_pair.first;
        buffer.Trim();
        if (buffer.GetLength() == 0 || section_pair.second.GetEntities().size() == 0)
            sectionsToRemove.push_back(section_pair.first);

        std::vector<ppmfc::CString> keysToRemove;
        for (auto& key_pair : section_pair.second.GetEntities())
        {
            buffer = key_pair.first;
            buffer.Trim();
            if (buffer.GetLength() == 0)
                keysToRemove.push_back(key_pair.first);
        }

        for (auto& key : keysToRemove)
            pINI->DeleteKey(section_pair.first, key);

        if (section_pair.second.GetEntities().size() == 0)
            sectionsToRemove.push_back(section_pair.first);
    }
    for (auto& section : sectionsToRemove)
        pINI->DeleteSection(section);

    if (previewOption == 2)
    {
        // No preview / hidden preview.
        Logger::Raw("SaveMap : Generating a hidden map preview.\n");
        pINI->DeleteSection("Preview");
        pINI->DeleteSection("PreviewPack");
        pINI->WriteString("Preview", "Size", "0,0,106,61");
        pINI->WriteString("PreviewPack", "1", "BIACcgAEwBtAMnRABAAaQCSANMAVQASAAnIABMAbQDJ0QAQAGkAkgDTAFUAEgAJyAATAG0");
        pINI->WriteString("PreviewPack", "2", "yAsAIAXQ5PDQ5PDQ6JQATAEE6PDQ4PDI4JgBTAFEAkgAJyAATAG0AydEAEABpAJIA0wBVA");
    }
    else if (previewOption == 0)
    {
        // Generate new preview.
        Logger::Raw("SaveMap : Generating a new map preview.\n");
        CMapData::Instance->UpdateINIFile(SaveMapFlag::UpdatePreview);
    }
    else
    {
        // Do not update preview.
        Logger::Raw("SaveMap : Retaining current map preview.\n");
    }

    if (ExtConfigs::SaveMap_OnlySaveMAP)
    {
        int nExtIndex = filepath.ReverseFind('.');
        if (nExtIndex == -1)
            filepath += ".map";
        else
            filepath = filepath.Mid(0, nExtIndex) + ".map";
    }

    Logger::Raw("SaveMap : Trying to save map to %s.\n", filepath);
    
    std::ofstream fout;
    fout.open(filepath, std::ios::out | std::ios::trunc);

    if (fout.is_open())
    {
        fout <<
            "; Map created with FinalAlert 2(tm) Mission Editor\n"
            "; Get it at http://www.westwood.com\n"
            "; note that all comments were truncated\n"
            "\n"
            "; This FA2 uses FA2sp created by secsome\n"
            "; Get the lastest dll at https://github.com/secsome/FA2sp\n"
            "; Current version : " << PRODUCT_STR << "\n\n";

        // Dirty fix: vanilla YR needs "Preview" and "PreviewPack" before "Map"
        // So we just put them at first.
        if (const auto pSection = pINI->GetSection("Preview"))
        {
            fout << "[Preview]\n";
            for (const auto& pair : pSection->GetEntities())
                fout << pair.first << "=" << pair.second << "\n";
            fout << "\n";
        }
        if (const auto pSection = pINI->GetSection("PreviewPack"))
        {
            fout << "[PreviewPack]\n";
            for (const auto& pair : pSection->GetEntities())
                fout << pair.first << "=" << pair.second << "\n";
            fout << "\n";
        }

        for (auto& section : pINI->Dict)
        {
            if (!strcmp(section.first, "Preview") || !strcmp(section.first, "PreviewPack"))
                continue;

            fout << "[" << section.first << "]\n";
            for (auto& pair : section.second.GetEntities())
                fout << pair.first << "=" << pair.second << "\n";
            fout << "\n";
        }

        fout.flush();
        fout.close();

        Logger::Raw("SaveMap : Successfully saved %u sections.\n", pINI->Dict.size());
    }
    else
    {
        ppmfc::CString buffer;
        buffer.Format("Failed to create file %s.\n", filepath);
        Logger::Put(buffer);
        ::MessageBox(NULL, buffer, "Error", MB_OK | MB_ICONERROR);
    }

    return 0x42A859;

    return 0;
}

DEFINE_HOOK(42B30F, CFinalSunDlg_SaveMap_SkipMapDTOR, 7)
{
    return 0x42B323;
}

DEFINE_HOOK(42B2AF, CFinalSunDlg_SaveMap_SkipDeleteFile, 7)
{
    return 0x42B2C2;
}

DEFINE_HOOK(42A8F5, CFinalSunDlg_SaveMap_ReplaceCopyFile, 7)
{
    REF_STACK(ppmfc::CString, filepath, STACK_OFFS(0x3F4, -0x4));

    std::ifstream fin;
    fin.open(filepath, std::ios::in | std::ios::binary);
    if (fin.is_open())
    {
        fin.close();
        return 0x42A92D;
    }
    return 0x42A911;
}

DEFINE_HOOK(42B2EA, CFinalSunDlg_SaveMap_SkipStringDTOR, C)
{
    return 0x42B30F;
}

void SaveMapExt::ResetTimer()
{
    StopTimer();
    if (ExtConfigs::SaveMap_AutoSave_Interval >= 30)
    {
        if (Timer = SetTimer(NULL, NULL, 1000 * ExtConfigs::SaveMap_AutoSave_Interval, SaveMapCallback))
            Logger::Debug("Successfully created timer with ID = %p.\n", Timer);
        else
            Logger::Debug("Failed to create timer! Auto-save is currently unable to use!\n");
    }
}

void SaveMapExt::StopTimer()
{
    if (Timer != NULL)
    {
        KillTimer(NULL, Timer);
        Timer = NULL;
    }
}

void SaveMapExt::RemoveEarlySaves()
{
    if (ExtConfigs::SaveMap_AutoSave_MaxCount != -1)
    {
        struct FileTimeComparator
        {
            bool operator()(const FILETIME& a, const FILETIME& b) const { return CompareFileTime(&a, &b) == -1; }
        };

        std::map<FILETIME, ppmfc::CString, FileTimeComparator> m;
        auto mapName = CINI::CurrentDocument->GetString("Basic", "Name", "No Name");

        /*
        * Fix : Windows file name cannot begin with space and cannot have following characters:
        * \ / : * ? " < > |
        */
        for (int i = 0; i < mapName.GetLength(); ++i)
            if (mapName[i] == '\\' || mapName[i] == '/' || mapName[i] == ':' ||
                mapName[i] == '*' || mapName[i] == '?' || mapName[i] == '"' ||
                mapName[i] == '<' || mapName[i] == '>' || mapName[i] == '|'
                )
                mapName.SetAt(i, '-');

        const auto ext =
            !ExtConfigs::SaveMap_OnlySaveMAP && CMapData::Instance->IsMultiOnly() ?
            CLoading::HasMdFile() ?
            "yrm" :
            "mpr" :
            "map";

        ppmfc::CString buffer;
        buffer.Format("%s\\AutoSaves\\%s\\%s-*.%s",
            CFinalSunApp::ExePath(),
            mapName,
            mapName,
            ext
        );

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

        auto itr = m.begin();
        while (count != 0)
        {
            buffer.Format("%s\\AutoSaves\\%s\\%s", CFinalSunApp::ExePath(), mapName, itr->second);
            DeleteFile(buffer);
            ++itr;
            --count;
        }
    }
}

void CALLBACK SaveMapExt::SaveMapCallback(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
    Logger::Debug("SaveMapCallback called, trying to auto save map. hwnd = %08X, message = %d, iTimerID = %d, dwTime = %d.\n",
        hwnd, message, iTimerID, dwTime);

    if (!CMapData::Instance->MapWidthPlusHeight || !CMapData::Instance->FieldDataAllocated)
    {
        StopTimer();
        return;
    }

    SYSTEMTIME time;
    GetLocalTime(&time);

    auto mapName = CINI::CurrentDocument->GetString("Basic", "Name", "No Name");

    /*
    * Fix : Windows file name cannot begin with space and cannot have following characters:
    * \ / : * ? " < > |
    */
    for (int i = 0; i < mapName.GetLength(); ++i)
        if (mapName[i] == '\\' || mapName[i] == '/' || mapName[i] == ':' ||
            mapName[i] == '*' || mapName[i] == '?' || mapName[i] == '"' ||
            mapName[i] == '<' || mapName[i] == '>' || mapName[i] == '|'
            )
            mapName.SetAt(i, '-');

    const auto ext =
        !ExtConfigs::SaveMap_OnlySaveMAP && CMapData::Instance->IsMultiOnly() ?
        CLoading::HasMdFile() ?
        "yrm" :
        "mpr" :
        "map";

    ppmfc::CString buffer = CFinalSunApp::ExePath();
    buffer += "\\AutoSaves\\";
    CreateDirectory(buffer, nullptr);
    buffer += mapName;
    CreateDirectory(buffer, nullptr);

    buffer.Format("%s\\AutoSaves\\%s\\%s-%04d%02d%02d-%02d%02d%02d-%03d.%s",
        CFinalSunApp::ExePath(),
        mapName,
        mapName,
        time.wYear, time.wMonth, time.wDay,
        time.wHour, time.wMinute, time.wSecond,
        time.wMilliseconds,
        ext
    );

    IsAutoSaving = true;
    CFinalSunDlg::Instance->SaveMap(buffer);
    IsAutoSaving = false;

    RemoveEarlySaves();
}

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

DEFINE_HOOK(437D84, CFinalSunDlg_LoadMap_StopTimer, 5)
{
    if (ExtConfigs::SaveMap_AutoSave)
        SaveMapExt::StopTimer();
    return 0;
}

DEFINE_HOOK(438D90, CFinalSunDlg_LoadMap_ResetTimer, 7)
{
    if (ExtConfigs::SaveMap_AutoSave && CMapData::Instance->MapWidthPlusHeight)
        SaveMapExt::ResetTimer();
    return 0;
}

DEFINE_HOOK(42CBE0, CFinalSunDlg_CreateMap_StopTimer, 5)
{
    if (ExtConfigs::SaveMap_AutoSave)
        SaveMapExt::StopTimer();
    return 0;
}

DEFINE_HOOK(42E18E, CFinalSunDlg_CreateMap_ResetTimer, 7)
{
    if (ExtConfigs::SaveMap_AutoSave && CMapData::Instance->MapWidthPlusHeight)
        SaveMapExt::ResetTimer();
    return 0;
}