#pragma once

#include <stdarg.h>
#include <cstdio>

#include <string_view>
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
    static void Time(char*);
    static void Wrap(unsigned int cnt = 1);

    template <class... _Types>
    static void FormatLog(const std::string_view _Fmt, const _Types&... _Args) {
        Logger::Raw(std::format(_Fmt, _Args...).c_str());
    }

private:
    static char pTime[24];
    static char pBuffer[0x800];
    static FILE* pFile;
    static bool bInitialized;
};