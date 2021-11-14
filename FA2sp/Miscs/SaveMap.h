#pragma once

#include <Helpers/Macro.h>

#include "../FA2sp.h"

class SaveMapExt
{
private:
    static UINT_PTR Timer;
public:
    static bool IsAutoSaving;
    static ppmfc::CString FileName;

    static void ResetTimer();
    static void StopTimer();
    static void RemoveEarlySaves();
    static void CALLBACK SaveMapCallback(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime);
};