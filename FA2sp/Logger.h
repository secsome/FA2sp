#pragma once

#include <stdarg.h>
#include <cstdio>

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
private:
    static FILE* file_pointer_;
    static bool is_initialized_;
};