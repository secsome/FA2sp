#pragma once

#include <CINI.h>

class FAINIHelper
{
private:
    void InsertSectionHelper();

public:
    static bool InsertSection(const char* pSection);

public:
    static const char** pSection;
    static INISection* pReturn;
    static bool isHelper;
};

void FAINIHelper::InsertSectionHelper()
{
    isHelper = true;
    JMP_THIS(0x40ACE0);
    isHelper = false;
}

bool FAINIHelper::InsertSection(const char* pSection)
{
    FAINIHelper::pSection = &pSection;
    FAINIHelper helper;
    helper.InsertSectionHelper();
    FAINIHelper::pSection = nullptr;
    return pReturn != nullptr;
}

const char** FAINIHelper::pSection = nullptr;
INISection* FAINIHelper::pReturn = nullptr;
bool FAINIHelper::isHelper = false;

DEFINE_HOOK(40ACFF, FAINIHelper_InsertINI_1, 5)
{
    return FAINIHelper::isHelper ? 0x40AD3B : 0;
}

DEFINE_HOOK(40AD2B, FAINIHelper_InsertINI_2, 6)
{
    if (FAINIHelper::isHelper)
    {
        R->EAX(FAINIHelper::pSection);
        R->EDI(R->EAX());
        return 0x40AD31;
    }
    return 0;
}

DEFINE_HOOK(40AD4E, FAINIHelper_InsertINI_3, 7)
{
    FAINIHelper::pReturn = FAINIHelper::isHelper ? R->ESI<INISection*>() : nullptr;
    return 0;
}

DEFINE_HOOK(40AED6, FAINIHelper_InsertINI_4, 5)
{
    return FAINIHelper::isHelper ? 0x40AEDB : 0;
}