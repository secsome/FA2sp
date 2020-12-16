#include "Translations.h"

#include <GlobalVars.h>

CString FinalAlertConfig::lpPath;
char FinalAlertConfig::pLastRead[0x400];

// Same as ExeRun
DEFINE_HOOK(537129, Translations_Initialzation, 9)
{
    FinalAlertConfig::lpPath = GlobalVars::ExePath();
    FinalAlertConfig::lpPath += "FinalAlert.ini";
    FinalAlertConfig::ReadString("FinalSun", "Language", "English");
    strcpy_s(Translations::pLanguage[0], FinalAlertConfig::pLastRead);
    strcpy_s(Translations::pLanguage[1], FinalAlertConfig::pLastRead);
    strcat_s(Translations::pLanguage[0], "-Strings");
    strcat_s(Translations::pLanguage[1], "-StringsRA2");
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

char Translations::pLanguage[2][0x400];
bool Translations::GetTranslationItem(const char* pLabelName, CString& ret)
{
    auto& falanguage = GlobalVars::INIFiles::FALanguage();
    if (falanguage.SectionExists(pLanguage[0]))
    {
        auto& section = falanguage.GetSection(pLanguage[0]);
        auto itr = section.EntitiesDictionary.find(pLabelName);
        if (itr != section.EntitiesDictionary.end())
        {
            ret = itr->second;
            return true;
        }
    }
    if (falanguage.SectionExists(pLanguage[1]))
    {
        auto& section = falanguage.GetSection(pLanguage[1]);
        auto itr = section.EntitiesDictionary.find(pLabelName);
        if (itr != section.EntitiesDictionary.end())
        {
            ret = itr->second;
            return true;
        }
    }
    return false;
}