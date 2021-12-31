#include "Logger.h"
#include <windows.h>
#include <share.h>

char Logger::pTime[24];
char Logger::pBuffer[0x800];
FILE* Logger::pFile;
bool Logger::bInitialized;

void Logger::Initialize() {
	pFile = _fsopen("FA2sp.log", "w", _SH_DENYWR);
	bInitialized = pFile;
	Time(pTime);
	Raw("FA2sp Logger Initializing at %s.\n", pTime);
}

void Logger::Close() {
	if (bInitialized)
	{
		Time(pTime);
		Raw("FA2sp Logger Closing at %s.\n", pTime);
		fclose(pFile);
	}
}

void Logger::Write(kLoggerType type, const char* format, va_list args) {
	if (bInitialized) {
		vsprintf_s(pBuffer, format, args);
		char type_str[6];
		switch (type)
		{
		default:
		case Logger::kLoggerType::Raw:
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
		if (type == Logger::kLoggerType::Raw)
			fprintf_s(pFile, "%s", pBuffer);
		else
			fprintf_s(pFile, "[%s] %s", type_str, pBuffer);
		fflush(pFile);
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

void Logger::Put(const char* pBuffer) {
	if (bInitialized) {
		fputs(pBuffer, pFile);
		fflush(pFile);
	}
}

void Logger::Time(char* ret) {
	SYSTEMTIME Sys;
	GetLocalTime(&Sys);
	sprintf_s(ret, 24, "%04d/%02d/%02d %02d:%02d:%02d:%03d",
		Sys.wYear, Sys.wMonth, Sys.wDay, Sys.wHour, Sys.wMinute,
		Sys.wSecond, Sys.wMilliseconds);
}

void Logger::Wrap(unsigned int cnt) {
	if (bInitialized)
	{
		while (cnt--)
			fprintf_s(pFile, "\n");
		fflush(pFile);
	}
}