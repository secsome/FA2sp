#include "Body.h"

#include <Helpers/Macro.h>

#include <CINI.h>
#include <CMapData.h>
#include <CIsoView.h>

#include <set>

#include "../../Helpers/STDHelpers.h"

DEFINE_HOOK(4FA450, CTriggerFrame_Update, 7)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();
    const char* pData = nullptr;
    if (nCurSel != CB_ERR)
        pData = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel));

    while (pThis->CCBCurrentTrigger.DeleteString(0) != CB_ERR);

    pThis->CCBCurrentTrigger.SetWindowText("");

    if (auto pSection = CINI::CurrentDocument->GetSection("Triggers"))
    {
        for (auto& pair : pSection->EntitiesDictionary)
        {
            auto strs = STDHelpers::SplitString(pair.second);
            if (strs.size() != 7)
                continue;
            int nIdx = pThis->CCBCurrentTrigger.AddString(strs[2]);
            pThis->CCBCurrentTrigger.SetItemDataPtr(nIdx, pair.first.m_pchData);
        }
    }

    int nCount = pThis->CCBCurrentTrigger.GetCount();
    if (nCurSel < 0) nCurSel = 0;
    if (nCount >= nCurSel)
        nCurSel = nCount - 1;

    if (pData)
    {
        for (int i = 0; i < nCount; ++i)
        {
            if (strcmp(reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(i)), pData) == 0)
            {
                pThis->CCBCurrentTrigger.SetCurSel(i);
                break;
            }
        }
    }

    pThis->OnCBCurrentTriggerSelectedChanged();

    return 0x4FAACF;
}

DEFINE_HOOK(4FBA10, CTriggerFrame_OnCBCurrentTriggerEditChanged, 6)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();

    const char* TriggerID = "";
    if (nCurSel != CB_ERR)
    {
        if (auto ID = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel)))
            TriggerID = ID;
    }

    pThis->TriggerOption.TriggerID = pThis->TriggerEvent.TriggerID = pThis->TriggerAction.TriggerID = TriggerID;
    
    if (pThis->TriggerOption.m_hWnd)
        pThis->TriggerOption.Update();
    if (pThis->TriggerEvent.m_hWnd)
        pThis->TriggerEvent.Update();
    if (pThis->TriggerAction.m_hWnd)
        pThis->TriggerAction.Update();
    
    return 0x4FBAD3;
}

DEFINE_HOOK(4FAAD0, CTriggerFrame_OnBNNewTriggerClicked, 7)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    auto ID = CINI::GetAvailableIndex();
    auto Owner = CMapData::Instance->FindAvailableOwner(0, 1);
    auto TriggerBuffer = Owner + ",<none>,New trigger,0,1,1,1,0";

    CINI::CurrentDocument->WriteString("Triggers", ID, TriggerBuffer);
    CINI::CurrentDocument->WriteString("Events", ID, "0");
    CINI::CurrentDocument->WriteString("Actions", ID, "0");
    auto TagID = CINI::GetAvailableIndex();
    CINI::CurrentDocument->WriteString("Tags", TagID, "0,New tag," + ID);

    int nIndex = pThis->CCBCurrentTrigger.AddString("New Trigger");
    pThis->CCBCurrentTrigger.SetItemDataPtr(nIndex, ID.m_pchData);
    pThis->CCBCurrentTrigger.SetCurSel(nIndex);

    pThis->OnCBCurrentTriggerSelectedChanged();

    return 0x4FB1AD;
}

DEFINE_HOOK(4FB1B0, CTriggerFrame_OnBNDelTriggerClicked, 6)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();
    if (nCurSel != CB_ERR)
    {
        if (auto ID = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel)))
        {
            const char* pMessage =
                "If you want to delete all attached tags, too, press Yes.\n"
                "If you don't want to delete these tags, press No.\n"
                "If you want to cancel to deletion of the trigger, press Cancel.\n"
                "Note: CellTags will be deleted too using this function if you press Yes.";

            int nResult = pThis->MessageBox(pMessage, "Delete trigger", MB_YESNOCANCEL);
            if (nResult == IDOK || nResult == IDNO)
            {
                CINI::CurrentDocument->DeleteKey("Triggers", ID);
                CINI::CurrentDocument->DeleteKey("Events", ID);
                CINI::CurrentDocument->DeleteKey("Actions", ID);
                if (nResult == IDYES)
                {
                    if (auto pTagsSection = CINI::CurrentDocument->GetSection("Tags"))
                    {
                        std::set<ppmfc::CString> TagsToRemove;
                        for (auto& pair : pTagsSection->EntitiesDictionary)
                        {
                            auto splits = STDHelpers::SplitString(pair.second);
                            if (splits.size() == 3)
                            {
                                if (strcmp(splits[2], ID) == 0)
                                    TagsToRemove.insert(pair.first);
                            }
                        }
                        for (auto& tag : TagsToRemove)
                            CINI::CurrentDocument->DeleteKey("Tags", tag);

                        if (auto pCellTagsSection = CINI::CurrentDocument->GetSection("CellTags"))
                        {
                            std::vector<ppmfc::CString> CellTagsToRemove;
                            for (auto& pair : pCellTagsSection->EntitiesDictionary)
                            {
                                if (TagsToRemove.find(pair.second) != TagsToRemove.end())
                                    CellTagsToRemove.push_back(pair.first);
                            }
                            for (auto& celltag : CellTagsToRemove)
                                CINI::CurrentDocument->DeleteKey("CellTags", celltag);
                        }
                        
                    }
                    
                }
            }
        }
    }

    return 0x4FB9F3;
}

DEFINE_HOOK(4FBD10, CTriggerFrame_OnBNPlaceOnMapClicked, 6)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();
    if (nCurSel != CB_ERR)
    {
        if (auto ID = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel)))
        {
            if (auto pTagsSection = CINI::CurrentDocument->GetSection("Tags"))
            {
                for (auto& pair : pTagsSection->EntitiesDictionary)
                {
                    auto splits = STDHelpers::SplitString(pair.second);
                    if (splits.size() == 3)
                    {
                        if (strcmp(splits[2], ID) == 0)
                        {
                            CIsoView::CurrentCommand = 4;
                            CIsoView::CurrentType = 4;
                            CIsoView::CurrentObjectID.get() = splits[2];
                            break;
                        }
                    }
                }
            }
        }
    }

    return 0x4FC17B;
}

DEFINE_HOOK(4FC180, CTriggerFrame_OnBNCloneTriggerClicked, 6)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();
    if (nCurSel != CB_ERR)
    {
        if (auto CurrentID = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel)))
        {
            auto buffer = CINI::CurrentDocument->GetString("Triggers", CurrentID);
            auto splits = STDHelpers::SplitString(buffer);
            if (splits.size() == 7)
            {
                auto& Name = splits[2];
                auto NewID = CINI::GetAvailableIndex();

                buffer.Format("%s,%s,%s Clone,%s,%s,%s,%s",
                    splits[0], splits[1], splits[2], splits[3],
                    splits[4], splits[5], splits[6]);

                CINI::CurrentDocument->WriteString("Triggers", NewID, buffer);
                CINI::CurrentDocument->WriteString("Events", NewID, CINI::CurrentDocument->GetString("Events", CurrentID));
                CINI::CurrentDocument->WriteString("Actions", NewID, CINI::CurrentDocument->GetString("Actions", CurrentID));
                auto TagID = CINI::GetAvailableIndex();
                CINI::CurrentDocument->WriteString("Tags", TagID, "0,New tag," + NewID);

                int nIndex = pThis->CCBCurrentTrigger.AddString(Name + " Clone");
                pThis->CCBCurrentTrigger.SetItemDataPtr(nIndex, NewID.m_pchData);
                pThis->CCBCurrentTrigger.SetCurSel(nIndex);

                pThis->OnCBCurrentTriggerSelectedChanged();
            }
        }
    }

    return 0x4FCFAA;
}