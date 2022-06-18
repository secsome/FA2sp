#pragma once

#include <cstdarg>
#include <cstdio>
#include <format>

class Logger {
public:
    enum class kLoggerType { Raw = -1, Debug, Info, Warn, Error };
    static void Initialize();
    static void Close();
    static void Write(kLoggerType, const char*, va_list);
    static void Debug(const char*, ...);
    static void Info(const char*, ...);
    static void Warn(const char*, ...);
    static void Error(const char*, ...);
    static void Raw(const char*, ...);
    static void Put(const char*);
    static void Time(char*);
    static void Wrap(unsigned int cnt = 1);

private:
    static char pTime[24];
    static char pBuffer[0x800];
    static FILE* pFile;
    static bool bInitialized;
};