#include "Translations.h"

#include <Helpers/Macro.h>
#include <GlobalVars.h>
#include <CINI.h>

CString FinalAlertConfig::lpPath;
char FinalAlertConfig::pLastRead[0x400];

// Load after ExePath is initialized
DEFINE_HOOK(41F7F5, Translations_Initialzation, 9)
{
    FinalAlertConfig::lpPath = GlobalVars::ExePath();
    FinalAlertConfig::lpPath += "FinalAlert.ini";
    FinalAlertConfig::ReadString("FinalSun", "Language", "English");
    strcpy_s(Translations::pLanguage[0], FinalAlertConfig::pLastRead);
    strcpy_s(Translations::pLanguage[1], FinalAlertConfig::pLastRead);
    strcpy_s(Translations::pLanguage[2], FinalAlertConfig::pLastRead);
    strcpy_s(Translations::pLanguage[3], FinalAlertConfig::pLastRead);
    strcat_s(Translations::pLanguage[0], "-StringsRA2");
    strcat_s(Translations::pLanguage[1], "-TranslationsRA2");
    strcat_s(Translations::pLanguage[2], "-Strings");
    strcat_s(Translations::pLanguage[3], "-Translations");
    return 0;
}

DWORD FinalAlertConfig::ReadString(const char* pSection, const char* pKey, const char* pDefault, char* pBuffer)
{
    DWORD dwRet = GetPrivateProfileString(pSection, pKey, pDefault, FinalAlertConfig::pLastRead, 0x400, lpPath);
    if (pBuffer)
        strcpy_s(pBuffer, 0x400, pLastRead);
    return dwRet;
}
void FinalAlertConfig::WriteString(const char* pSection, const char* pKey, const char* pContent)
{
    WritePrivateProfileString(pSection, pKey, pContent, lpPath);
};

char Translations::pLanguage[4][0x400];
bool Translations::GetTranslationItem(const char* pLabelName, ppmfc::CString& ret)
{
    auto& falanguage = GlobalVars::INIFiles::FALanguage();

    for(const auto& language : Translations::pLanguage)
        if (auto section = falanguage.GetSection(language))
        {
            auto itr = section->EntitiesDictionary.find(pLabelName);
            if (itr != section->EntitiesDictionary.end())
            {
                ret = itr->second;
                return true;
            }
        }

        return false;
}

void Translations::TranslateItem(CWnd* pWnd, int nSubID, const char* lpKey)
{
    ppmfc::CString buffer;
    if (Translations::GetTranslationItem(lpKey, buffer))
        pWnd->SetDlgItemText(nSubID, buffer);
}

void Translations::TranslateItem(CWnd* pWnd, const char* lpKey)
{
    ppmfc::CString buffer;
    if (Translations::GetTranslationItem(lpKey, buffer))
        pWnd->SetWindowText(buffer);
}