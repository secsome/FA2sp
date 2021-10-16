#include <CMixFile.h>
#include <CLoading.h>
#include <FAMemory.h>
#include <CFinalSunApp.h>

#include "../FA2sp.h"

#include <map>
#include <fstream>

class StringtableLoader
{
public:
    static void LoadCSFFiles();
    static void LoadCSFFile(const char* pName);
    static bool ParseCSFFile(char* buffer, DWORD size);
    static void WriteCSFFile();
    static bool LoadToBuffer();

    static std::map<CString, CString> CSFFiles_Stringtable;
    static char* pEDIBuffer;
    static bool bLoadRes;
};

bool StringtableLoader::bLoadRes = false;
char* StringtableLoader::pEDIBuffer = nullptr;
std::map<CString, CString> StringtableLoader::CSFFiles_Stringtable;

DEFINE_HOOK(492D10, CSFFiles_Stringtables_Support_1, 5)
{
    if (ExtConfigs::Stringtables)
    {
        StringtableLoader::LoadCSFFiles();
        StringtableLoader::bLoadRes = StringtableLoader::LoadToBuffer();
        if (StringtableLoader::bLoadRes)
        {
            R->EDI(StringtableLoader::pEDIBuffer);
            return 0x49305F;
        }
        else
            return 0;
    }
    return 0;
}

DEFINE_HOOK(49433B, CSFFiles_Stringtables_Support_2, 6)
{
    // Cleanning up
    if (ExtConfigs::Stringtables && StringtableLoader::bLoadRes)
    {
        GameDelete(StringtableLoader::pEDIBuffer);
        char tmpCsfFile[0x400];
        strcpy_s(tmpCsfFile, CFinalSunApp::ExePath());
        strcat_s(tmpCsfFile, "\\RA2Tmp.csf");
        DeleteFile(tmpCsfFile);
        Logger::Debug("Successfully loaded %d csf labels.\n", StringtableLoader::CSFFiles_Stringtable.size());
        StringtableLoader::CSFFiles_Stringtable.clear();
        StringtableLoader::bLoadRes = false;
    }
    return 0;
}

void StringtableLoader::LoadCSFFiles()
{
    char nameBuffer[0x400];
    if (CLoading::HasMdFile())
        strcpy_s(nameBuffer, "RA2MD.CSF");
    else
        strcpy_s(nameBuffer, "RA2.CSF");
    LoadCSFFile(nameBuffer);
    char stringtable[20];
    for (int i = 1; i <= 99; ++i)
    {
        sprintf_s(stringtable, "stringtable%02d.csf", i);
        LoadCSFFile(stringtable);
    }
    WriteCSFFile();
}

void StringtableLoader::LoadCSFFile(const char* pName)
{
    HANDLE hFile = INVALID_HANDLE_VALUE;
    char directoryBuffer[0x400];
    strcpy_s(directoryBuffer, CFinalSunApp::FilePath());
    strcat_s(directoryBuffer, "\\");
    strcat_s(directoryBuffer, pName);
    
    DWORD dwSize;
    if (auto pBuffer = CLoading::Instance->ReadWholeFile(pName, &dwSize))
        if (ParseCSFFile((char*)pBuffer, dwSize))
            Logger::Debug("Successfully Loaded file %s.\n", pName);
}

bool StringtableLoader::ParseCSFFile(char* buffer, DWORD size)
{
    char* pos = buffer;

    auto read_int = [&pos](const void* dest)
    {
        memcpy((void*)dest, pos, 4);
        pos += 4;
    };

    // Parse CSF header
    if (memcmp(pos, " FSC", 0x4) != 0) {
        return false;
    }
    pos += 4; // FSC
    pos += 4; // version
    int _numLabels;
    read_int(&_numLabels);
    pos += 4; // numstrings
    pos += 4; // useless
    pos += 4; // lang
    // Read CSF labels
    for (int i = 0; i < _numLabels; ++i)
    {
        // Read CSF label header
        int identifier;
        read_int(&identifier);
        if (identifier == 0x4C424C20) // " LBL"
        {
            int numPairs;
            read_int(&numPairs);
            int strLength;
            read_int(&strLength);
            
            char* labelstr = new char[strLength + 1];
            labelstr[strLength] = '\0';
            memcpy_s(labelstr, strLength, pos, strLength);

            pos += strLength;
            // CSF labels are not case sensitive.
            for (int k = 0; k < strLength; ++k)
                labelstr[k] = tolower(labelstr[k]);

            read_int(&identifier);
            read_int(&strLength);

            char* tmpWideBuffer = new char[(strLength << 1) + 2];
            for (int i = 0; i < strLength << 1; ++i)
                tmpWideBuffer[i] = ~pos[i];
            wchar_t* ptrWideBuffer = reinterpret_cast<wchar_t*>(tmpWideBuffer);
            ptrWideBuffer[strLength] = '\0';
            
            char* value = nullptr;
            int valueBufferSize = WideCharToMultiByte(CP_ACP, NULL, ptrWideBuffer, strLength, value, 0, NULL, NULL) + 1;
            value = new char[valueBufferSize];
            WideCharToMultiByte(CP_ACP, NULL, ptrWideBuffer, strLength, value, valueBufferSize, NULL, NULL);
            delete[] tmpWideBuffer;
            value[valueBufferSize - 1] = '\0';

            pos += (strLength << 1);
            if (identifier == 0x53545257)
            {
                read_int(&strLength);
                pos += strLength;
            }
            StringtableLoader::CSFFiles_Stringtable[labelstr] = CString(value);
            if (ExtConfigs::TutorialTexts_Fix)
                FA2sp::TutorialTextsMap[labelstr] = value;
            delete[] labelstr;
            delete[] value;

            for (int j = 1; j < numPairs; ++j)
            {
                read_int(&identifier);
                read_int(&strLength);
                pos += (strLength << 1);
                if (identifier == 0x53545257)
                {
                    read_int(&strLength);
                    pos += strLength;
                }
            }
        }
        else {
            break;
        }
    }
    return true;
}

void StringtableLoader::WriteCSFFile()
{
    char tmpCsfFile[0x400];
    strcpy_s(tmpCsfFile, CFinalSunApp::ExePath());
    strcat_s(tmpCsfFile, "\\RA2Tmp.csf");
    std::ofstream fout;
    fout.open(tmpCsfFile, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!fout.is_open())
        return;

    auto write_to_stream = [&fout](const void* buffer, size_t size = 4) {
        fout.write((char*)buffer, size);
    };

    auto write_int = [&fout](int n) {
        fout.write((char*)&n, 4);
    };

    // CSF header
    write_to_stream(" FSC");
    write_int(3);
    write_int(StringtableLoader::CSFFiles_Stringtable.size());
    write_int(StringtableLoader::CSFFiles_Stringtable.size());
    write_to_stream("sFA2"); // useless
    write_int(0);

    // CSF labels
    for (auto& lbl : StringtableLoader::CSFFiles_Stringtable)
    {
        // label
        write_to_stream(" LBL");
        write_int(1);
        write_int(lbl.first.GetLength());
        write_to_stream(lbl.first, lbl.first.GetLength());

        // value
        write_to_stream(" RTS");
        wchar_t* value = nullptr;
        int valueBufferSize = MultiByteToWideChar(CP_ACP, NULL, lbl.second, lbl.second.GetLength(), value, 0);
        value = new wchar_t[valueBufferSize + 1];
        MultiByteToWideChar(CP_ACP, NULL, lbl.second, lbl.second.GetLength(), value, valueBufferSize);
        value[valueBufferSize] = '\0';
        char* buffer = reinterpret_cast<char*>(value);
        for (int i = 0; i < valueBufferSize << 1; ++i)
            buffer[i] = ~buffer[i];
        write_int(valueBufferSize);
        write_to_stream(buffer, valueBufferSize << 1);
        delete[] value;
    }
    fout.close();
}

bool StringtableLoader::LoadToBuffer()
{
    char directoryBuffer[0x400];
    strcpy_s(directoryBuffer, CFinalSunApp::ExePath());
    strcat_s(directoryBuffer, "\\");
    strcat_s(directoryBuffer, "RA2Tmp.csf");
    std::ifstream fin;
    fin.open(directoryBuffer, std::ios::in | std::ios::binary);
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end);
        const int size = static_cast<int>(fin.tellg());
        if (size == 0)
            return false;
        fin.seekg(0, std::ios::beg);
        StringtableLoader::pEDIBuffer = GameCreateArray<char>(size);
        bool result = false;
        if (StringtableLoader::pEDIBuffer)
            fin.read(StringtableLoader::pEDIBuffer, size);
        fin.close();
        return true;
    }
    return false;
}