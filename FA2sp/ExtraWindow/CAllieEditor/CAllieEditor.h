#pragma once

#include <FA2PP.h>
#include <CHouses.h>
#include <CFinalSunDlg.h>

class CAllieEditor
{
public:
    static void Create();

protected:
    static BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:

};