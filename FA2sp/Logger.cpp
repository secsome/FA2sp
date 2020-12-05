#include "Logger.h"
#include <windows.h>
#include <share.h>

FILE* Logger::file_pointer_;
bool Logger::is_initialized_;

void Logger::Initialize() {
	file_pointer_ = _fsopen("FA2sp.log", "w", _SH_DENYWR);
	is_initialized_ = file_pointer_;
	char time[24];
	Time(time);
	Raw("FA2sp Logger Initializing at %s ", time);
}

void Logger::Close() {
	char time[24];
	Time(time);
	Raw("FA2sp Logger Closing at %s ", time);
	fclose(file_pointer_);
}

void Logger::Write(kLoggerType type, const char* format, va_list args) {
	if (is_initialized_) {
		char buffer[0x800];
		vsprintf_s(buffer, format, args);
		char type_str[6];
		switch (type)
		{
		default:
		case Logger::kLoggerType::Raw:
			strcpy_s(type_str, 6, "");
			break;
		case Logger::kLoggerType::Debug:
			strcpy_s(type_str, 6, "Debug");
			break;
		case Logger::kLoggerType::Info:
			strcpy_s(type_str, 6, "Info");
			break;
		case Logger::kLoggerType::Warn:
			strcpy_s(type_str, 6, "Warn");
			break;
		case Logger::kLoggerType::Error:
			strcpy_s(type_str, 6, "Error");
			break;
		}
		fprintf_s(file_pointer_, "[%s] %s", type_str, buffer);
		fflush(file_pointer_);
	}
}

void Logger::Debug(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Write(kLoggerType::Debug, format, args);
	va_end(format);
}

void Logger::Warn(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Write(kLoggerType::Warn, format, args);
	va_end(format);
}

void Logger::Error(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Write(kLoggerType::Error, format, args);
	va_end(format);
}

void Logger::Info(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Write(kLoggerType::Info, format, args);
	va_end(format);
}

void Logger::Raw(const char* format, ...) {
	va_list args;
	va_start(args, format);
	Write(kLoggerType::Raw, format, args);
	va_end(format);
}

void Logger::Time(char* ret) {
	SYSTEMTIME Sys;
	GetLocalTime(&Sys);
	sprintf_s(ret, 24, "%04d/%02d/%02d %02d:%02d:%02d:%03d",
		Sys.wYear, Sys.wMonth, Sys.wDay, Sys.wHour, Sys.wMinute,
		Sys.wSecond, Sys.wMilliseconds);
}