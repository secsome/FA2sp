#pragma once

#include <FA2PP.h>

// FinalAlert.ini
class FinalAlertConfig
{
public:
    static DWORD ReadString(const char* pSection, const char* pKey, const char* pDefault = "", char* pBuffer = nullptr);
    static void WriteString(const char* pSection, const char* pKey, const char* pContent);
    static char pLastRead[0x400];
    static CString lpPath;
};

class Translations
{
public:
    static bool GetTranslationItem(const char* pLabelName, ppmfc::CString& ret);
    static void TranslateItem(CWnd* pWnd, int nSubID, const char* lpKey);
    static void TranslateItem(CWnd* pWnd, const char* lpKey);
    static void TranslateItem(ppmfc::CWnd* pWnd, int nSubID, const char* lpKey) { TranslateItem((CWnd*)pWnd, nSubID, lpKey); }
    static void TranslateItem(ppmfc::CWnd* pWnd, const char* lpKey) { TranslateItem((CWnd*)pWnd, lpKey); };
    static const char* TranslateOrDefault(const char* lpLabelName, const char* lpDefault);
    static char pLanguage[4][0x400];
};

