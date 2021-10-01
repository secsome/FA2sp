#pragma once

#include "../Body.h"

#include <map>
#include <vector>

class TriggerSort
{
public:
    static TriggerSort Instance;

    TriggerSort() : m_hWnd{ NULL } {}

    void LoadAllTriggers();
    void Clear();
    BOOL OnNotify(LPNMTREEVIEW lpNmhdr);
    BOOL OnMessage(PMSG pMsg);
    void Create(HWND hParent);
    void OnSize() const;
    void ShowWindow(bool bShow) const;
    void ShowWindow() const;
    void HideWindow() const;
    bool IsValid() const;
    bool IsVisible() const;
    HWND GetHwnd() const;
    operator HWND() const;

private:
    HTREEITEM FindLabel(HTREEITEM hItemParent, LPCSTR pszLabel) const;
    std::vector<ppmfc::CString> GetGroup(ppmfc::CString& triggerId, ppmfc::CString& name) const;
    void AddTrigger(std::vector<ppmfc::CString>&& group, ppmfc::CString& name, ppmfc::CString& id) const;
    void AddTrigger(ppmfc::CString triggerId) const;

private:
    HWND m_hWnd;
};