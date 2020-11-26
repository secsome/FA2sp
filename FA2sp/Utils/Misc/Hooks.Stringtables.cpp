#include <CMixFile.h>
#include <GlobalVars.h>

#include "../../FA2sp.h"

void LoadCSFFiles(DWORD pThisAddr);
void LoadCSFFile(const char* tmpFilePath, const char* pName, DWORD& pThisAddr);
bool ParseCSFFile(char* buffer, DWORD& size);

DEFINE_HOOK(492C40, CSFFiles_ReadFiles, 7)
{
    LoadCSFFiles(R->ECX());
    *reinterpret_cast<char*>(0x7EE084) = 9;
    return 0x494341;
}

void LoadCSFFiles(DWORD pThisAddr)
{
    char tmpCsfFile[0x400];
    strcpy_s(tmpCsfFile, GlobalVars::ExePath());
    strcat_s(tmpCsfFile, "\\RA2Tmp.csf");

    char nameBuffer[0x400];
    if (*reinterpret_cast<bool*>(0x5D32AC))
        strcpy_s(nameBuffer, "RA2MD.CSF");
    else
        strcpy_s(nameBuffer, "RA2.CSF");
    LoadCSFFile(tmpCsfFile, nameBuffer, pThisAddr);
    char stringtable[20];
    for (int i = 1; i <= 99; ++i)
    {
        sprintf_s(stringtable, "stringtable%02d.csf", i);
        LoadCSFFile(tmpCsfFile, stringtable, pThisAddr);
    }
}

void LoadCSFFile(const char* tmpFilePath, const char* pName, DWORD& pThisAddr)
{
    HANDLE hFile = INVALID_HANDLE_VALUE;
    char directoryBuffer[0x400];
    strcpy_s(directoryBuffer, GlobalVars::FilePath());
    strcat_s(directoryBuffer, "\\");
    strcat_s(directoryBuffer, pName);
    hFile = CreateFile(directoryBuffer, GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        if (!CMixFile::FindAndCopyTo(pName, tmpFilePath, pThisAddr))
            goto failed;
        hFile = CreateFile(tmpFilePath, GENERIC_READ, FILE_SHARE_READ, nullptr,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE)
            goto failed;
    }
    DWORD filesize = GetFileSize(hFile, nullptr);
    ULONG nReadBytes;
    char* fileBuffer = new char[filesize];
    if (ReadFile(hFile, fileBuffer, filesize, &nReadBytes, nullptr) == FALSE)
        goto failed;
    bool result = ParseCSFFile(fileBuffer, filesize);
    delete fileBuffer;
    DeleteFile(tmpFilePath);
    if (result)
        goto succeed;
    else
        goto failed;

failed:
    Logger::Debug("Cannot read %s while parsing CSFFiles.\n", pName);
    CloseHandle(hFile);
    return;
succeed:
    Logger::Debug("Successfully Loaded file %s.\n", pName);
    CloseHandle(hFile);
    return;
}

bool ParseCSFFile(char* buffer, DWORD& size)
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
            char* value = new char[strLength << 1 | 1];
            size_t tmp;
            
            wcstombs_s(&tmp, value, strLength << 1 | 1, ptrWideBuffer, strLength);

            pos += (strLength << 1);
            if (identifier == 0x53545257)
            {
                read_int(&strLength);
                pos += strLength;
            }
            FA2sp::StringTableDictionary[labelstr] = value;
            delete labelstr;
            delete value;

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