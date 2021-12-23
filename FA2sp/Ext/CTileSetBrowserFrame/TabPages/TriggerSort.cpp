#include "TriggerSort.h"

#include "../../../FA2sp.h"
#include "../../../Helpers/STDHelpers.h"

#include <CFinalSunDlg.h>

TriggerSort TriggerSort::Instance;

void TriggerSort::LoadAllTriggers()
{
    this->Clear();

    // TODO : 
    // Optimisze the efficiency
    if (auto pSection = CINI::CurrentDocument->GetSection("Triggers"))
    {
        for (auto& pair : pSection->GetEntities())
        {
            this->AddTrigger(pair.first);
        }
    }
}

void TriggerSort::Clear()
{
    TreeView_DeleteAllItems(this->GetHwnd());
}

BOOL TriggerSort::OnNotify(LPNMTREEVIEW lpNmTreeView)
{
    switch (lpNmTreeView->hdr.code)
    {
    case TVN_SELCHANGED:
        if (auto pID = reinterpret_cast<const char*>(lpNmTreeView->itemNew.lParam))
        {
            if (strlen(pID))
            {
                if (CFinalSunDlg::Instance->TriggerFrame.m_hWnd)
                {
                    auto pStr = CINI::CurrentDocument->GetString("Triggers", pID);
                    auto results = STDHelpers::SplitString(pStr);
                    if (results.size() <= 3)
                        return FALSE;
                    pStr = results[2];
                    auto idx = CFinalSunDlg::Instance->TriggerFrame.CCBCurrentTrigger.FindStringExact(0, pStr);
                    if (idx == CB_ERR)
                        return FALSE;
                    CFinalSunDlg::Instance->TriggerFrame.CCBCurrentTrigger.SetCurSel(idx);
                    CFinalSunDlg::Instance->TriggerFrame.OnCBCurrentTriggerSelectedChanged();
                    return TRUE;
                }
                else
                    return FALSE;
            }
        }
        break;
    default:
        break;
    }

    return FALSE;
}

BOOL TriggerSort::OnMessage(PMSG pMsg)
{
    switch (pMsg->message)
    {
    case WM_RBUTTONDOWN:
        this->ShowMenu(pMsg->pt);
        return TRUE;
    default:
        break;
    }

    return FALSE;
}

void TriggerSort::Create(HWND hParent)
{
    RECT rect;
    ::GetClientRect(hParent, &rect);

    this->m_hWnd = CreateWindowEx(NULL, "SysTreeView32", nullptr,
        WS_CHILD | WS_BORDER | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | 
        TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hParent,
        NULL, static_cast<HINSTANCE>(FA2sp::hInstance), nullptr);
}

void TriggerSort::OnSize() const
{
    RECT rect;
    ::GetClientRect(::GetParent(this->GetHwnd()), &rect);
    ::MoveWindow(this->GetHwnd(), 2, 29, rect.right - rect.left - 6, rect.bottom - rect.top - 35, FALSE);
}

void TriggerSort::ShowWindow(bool bShow) const
{
    ::ShowWindow(this->GetHwnd(), bShow ? SW_SHOW : SW_HIDE);
}

void TriggerSort::ShowWindow() const
{
    this->ShowWindow(true);
}

void TriggerSort::HideWindow() const
{
    this->ShowWindow(false);
}

void TriggerSort::ShowMenu(POINT pt) const
{
    HMENU hPopupMenu = ::CreatePopupMenu();
    ::AppendMenu(hPopupMenu, MF_STRING, (UINT_PTR)MenuItem::AddTrigger, "New Trigger from this group");
    ::TrackPopupMenu(hPopupMenu, TPM_VERTICAL | TPM_HORIZONTAL, pt.x, pt.y, NULL, this->GetHwnd(), nullptr);
}

bool TriggerSort::IsValid() const
{
    return this->GetHwnd() != NULL;
}

bool TriggerSort::IsVisible() const
{
    return this->IsValid() && ::IsWindowVisible(this->m_hWnd);
}

void TriggerSort::Menu_AddTrigger()
{
    HTREEITEM hItem = TreeView_GetSelection(this->GetHwnd());
    ppmfc::CString prefix = "";
    if (hItem != NULL)
    {
        const char* pID = nullptr;
        while (true)
        {
            TVITEM tvi;
            tvi.hItem = hItem;
            TreeView_GetItem(this->GetHwnd(), &tvi);
            if (pID = reinterpret_cast<const char*>(tvi.lParam))
                break;
            hItem = TreeView_GetChild(this->GetHwnd(), hItem);
            if (hItem == NULL)
            {
                this->m_strPrefix = prefix;
                return;
            }
        }

        ppmfc::CString buffer;
        prefix += "[";
        for (auto group : this->GetGroup(pID, buffer))
            prefix += group + ".";
        if (prefix[prefix.GetLength() - 1] == '.')
        {
            prefix.SetAt(prefix.GetLength() - 1, ']');
            if (prefix.GetLength() == 2)
                prefix = "";
        }
        else
            prefix = "";
    }
    this->m_strPrefix = prefix;
}

const ppmfc::CString& TriggerSort::GetCurrentPrefix() const
{
    return this->m_strPrefix;
}

HWND TriggerSort::GetHwnd() const
{
    return this->m_hWnd;
}

TriggerSort::operator HWND() const
{
    return this->GetHwnd();
}

HTREEITEM TriggerSort::FindLabel(HTREEITEM hItemParent, LPCSTR pszLabel) const
{
    TVITEM tvi;
    char chLabel[0x200];

    for (tvi.hItem = TreeView_GetChild(this->GetHwnd(), hItemParent); tvi.hItem;
        tvi.hItem = TreeView_GetNextSibling(this->GetHwnd(), tvi.hItem))
    {
        tvi.mask = TVIF_TEXT | TVIF_CHILDREN;
        tvi.pszText = chLabel;
        tvi.cchTextMax = _countof(chLabel);
        if (TreeView_GetItem(this->GetHwnd(), &tvi))
        {
            if (strcmp(tvi.pszText, pszLabel) == 0)
                return tvi.hItem;
            if (tvi.cChildren)
            {
                HTREEITEM hChildSearch = this->FindLabel(tvi.hItem, pszLabel);
                if (hChildSearch) 
                    return hChildSearch;
            }
        }
    }
    return NULL;
}

std::vector<ppmfc::CString> TriggerSort::GetGroup(ppmfc::CString triggerId, ppmfc::CString& name) const
{
    auto pSrc = CINI::CurrentDocument->GetString("Triggers", triggerId, "");

    auto ret = STDHelpers::SplitString(pSrc, 2);
    pSrc = ret[2];
    int nStart = pSrc.Find('[');
    int nEnd = pSrc.Find(']');
    if (nStart < nEnd)
    {
        name = pSrc.Mid(nEnd + 1);
        pSrc = pSrc.Mid(nStart + 1, nEnd - nStart - 1);
        ret = STDHelpers::SplitString(pSrc, ".");
        return ret;
    }
    else
        name = pSrc;
    
    ret.clear();
    return ret;
}

void TriggerSort::AddTrigger(std::vector<ppmfc::CString>&& group, ppmfc::CString name, ppmfc::CString id) const
{
    HTREEITEM hParent = TVI_ROOT;
    for (auto& node : group)
    {
        if (HTREEITEM hNode = this->FindLabel(hParent, node))
        {
            hParent = hNode;
            continue;
        }
        else
        {
            TVINSERTSTRUCT tvis;
            tvis.hInsertAfter = TVI_SORT;
            tvis.hParent = hParent;
            tvis.item.mask = TVIF_TEXT | TVIF_PARAM;
            tvis.item.lParam = NULL;
            tvis.item.pszText = node.m_pchData;
            hParent = TreeView_InsertItem(this->GetHwnd(), &tvis);
        }
    }

    if (HTREEITEM hNode = this->FindLabel(hParent, name))
    {
        TVITEM item;
        item.hItem = hNode;
        if (TreeView_GetItem(this->GetHwnd(), &item))
        {
            strcat(item.pszText, " (" + id + ")");
            item.lParam = (LPARAM)id.m_pchData;
            TreeView_SetItem(this->GetHwnd(), &item);
        }
    }
    else
    {
        TVINSERTSTRUCT tvis;
        tvis.hInsertAfter = TVI_SORT;
        tvis.hParent = hParent;
        tvis.item.mask = TVIF_TEXT | TVIF_PARAM;
        tvis.item.pszText = name.m_pchData;
        strcat(tvis.item.pszText, " (" + id + ")");
        tvis.item.lParam = (LPARAM)id.m_pchData;
        TreeView_InsertItem(this->GetHwnd(), &tvis);
    }
}

void TriggerSort::AddTrigger(ppmfc::CString triggerId) const
{
    if (this->IsVisible())
    {
        ppmfc::CString name;
        auto group = this->GetGroup(triggerId, name);
        this->AddTrigger(std::move(group), name, triggerId);
    }
}

void TriggerSort::DeleteTrigger(ppmfc::CString triggerId, HTREEITEM hItemParent) const
{
    if (this->IsVisible())
    {
        TVITEM tvi;

        for (tvi.hItem = TreeView_GetChild(this->GetHwnd(), hItemParent); tvi.hItem;
            tvi.hItem = TreeView_GetNextSibling(this->GetHwnd(), tvi.hItem))
        {
            tvi.mask = TVIF_PARAM | TVIF_CHILDREN;
            if (TreeView_GetItem(this->GetHwnd(), &tvi))
            {
                if (tvi.lParam && strcmp((const char*)tvi.lParam, triggerId) == 0)
                {
                    TreeView_DeleteItem(this->GetHwnd(), tvi.hItem);
                    return;
                }
                if (tvi.cChildren)
                    this->DeleteTrigger(triggerId, tvi.hItem);
            }
        }
    }
}

DEFINE_HOOK(4FA450, CTriggerFrame_Update_TriggerSort, 7)
{
    if(TriggerSort::Instance.IsVisible())
        TriggerSort::Instance.LoadAllTriggers();
    return 0;
}