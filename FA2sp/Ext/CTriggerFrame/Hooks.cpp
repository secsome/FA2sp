#include "Body.h"

#include <Helpers/Macro.h>

#include <CINI.h>
#include <CMapData.h>
#include <CIsoView.h>

#include <set>

#include "../CTileSetBrowserFrame/TabPages/TriggerSort.h"
#include "../../Helpers/STDHelpers.h"

DEFINE_HOOK(4FA450, CTriggerFrame_Update, 7)
{
    GET(CTriggerFrameExt*, pThis, ECX);

    int nFinalSel = CB_ERR;
    int nCurSel = pThis->CCBCurrentTrigger.GetCurSel();
    const char* ID = nullptr;
    if (nCurSel != CB_ERR)
        ID = reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(nCurSel));

    pThis->CCBCurrentTrigger.DeleteAllStrings();

    pThis->CCBCurrentTrigger.SetWindowText("");

    if (auto pSection = CINI::CurrentDocument->GetSection("Triggers"))
    {
        for (auto& pair : pSection->GetEntities())
        {
            auto splits = STDHelpers::SplitString(pair.second, 2);
            int nIdx = pThis->CCBCurrentTrigger.AddString(splits[2]);
            pThis->CCBCurrentTrigger.SetItemDataPtr(nIdx, pair.first.m_pchData);
        }
    }

    int nCount = pThis->CCBCurrentTrigger.GetCount();

    if (ID)
    {
        for (int i = 0; i < nCount; ++i)
        {
            if (strcmp(reinterpret_cast<const char*>(pThis->CCBCurrentTrigger.GetItemDataPtr(i)), ID) == 0)
            {
                nFinalSel = i;
                break;
            }
        }
    }

    if (nCurSel == 0) nCurSel = 1;
    if (nFinalSel < 0 && nCount > 0)
        nFinalSel = nCount - 1;

    pThis->CCBCurrentTrigger.SetCurSel(nFinalSel);
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
    ppmfc::CString Name =
        CTriggerFrameExt::CreateFromTriggerSort ?
        TriggerSort::Instance.GetCurrentPrefix() + "New Trigger" : 
        "New Trigger";

    auto TriggerBuffer = Owner + ",<none>,"+ Name + ",0,1,1,1,0";

    CINI::CurrentDocument->WriteString("Triggers", ID, TriggerBuffer);
    CINI::CurrentDocument->WriteString("Events", ID, "0");
    CINI::CurrentDocument->WriteString("Actions", ID, "0");
    auto TagID = CINI::GetAvailableIndex();
    CINI::CurrentDocument->WriteString("Tags", TagID, "0," + Name + " 1," + ID);

    int nIndex = pThis->CCBCurrentTrigger.AddString(Name);
    pThis->CCBCurrentTrigger.SetItemDataPtr(nIndex, ID.m_pchData);
    pThis->CCBCurrentTrigger.SetCurSel(nIndex);

    pThis->OnCBCurrentTriggerSelectedChanged();

    TriggerSort::Instance.AddTrigger(ID);

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
            if (nResult == IDYES || nResult == IDNO)
            {
                TriggerSort::Instance.DeleteTrigger(ID);
                CINI::CurrentDocument->DeleteKey("Triggers", ID);
                CINI::CurrentDocument->DeleteKey("Events", ID);
                CINI::CurrentDocument->DeleteKey("Actions", ID);
                if (nResult == IDYES)
                {
                    if (auto pTagsSection = CINI::CurrentDocument->GetSection("Tags"))
                    {
                        std::set<ppmfc::CString> TagsToRemove;
                        for (auto& pair : pTagsSection->GetEntities())
                        {
                            auto splits = STDHelpers::SplitString(pair.second, 2);
                            if (strcmp(splits[2], ID) == 0)
                                TagsToRemove.insert(pair.first);
                        }
                        for (auto& tag : TagsToRemove)
                            CINI::CurrentDocument->DeleteKey("Tags", tag);

                        if (auto pCellTagsSection = CINI::CurrentDocument->GetSection("CellTags"))
                        {
                            std::vector<ppmfc::CString> CellTagsToRemove;
                            for (auto& pair : pCellTagsSection->GetEntities())
                            {
                                if (TagsToRemove.find(pair.second) != TagsToRemove.end())
                                    CellTagsToRemove.push_back(pair.first);
                            }
                            for (auto& celltag : CellTagsToRemove)
                            {
                                CINI::CurrentDocument->DeleteKey("CellTags", celltag);
                                int nCoord = atoi(celltag);
                                int nMapCoord = CMapData::Instance->GetCoordIndex(nCoord % 1000, nCoord / 1000);
                                CMapData::Instance->CellDatas[nMapCoord].CellTag = -1;
                            }
                        }
                        
                    }
                    
                }
                pThis->CCBCurrentTrigger.DeleteString(nCurSel);
                if (--nCurSel >= 0)
                {
                    pThis->CCBCurrentTrigger.SetCurSel(nCurSel);
                    pThis->OnCBCurrentTriggerSelectedChanged();
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
                for (auto& pair : pTagsSection->GetEntities())
                {
                    auto splits = STDHelpers::SplitString(pair.second, 2);
                    if (strcmp(splits[2], ID) == 0)
                    {
                        CIsoView::CurrentCommand->Command = 4;
                        CIsoView::CurrentCommand->Type = 4;
                        CIsoView::CurrentCommand->ObjectID = pair.first;
                        break;
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
            auto splits = STDHelpers::SplitString(buffer, 7);
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

            TriggerSort::Instance.AddTrigger(NewID);
        }
    }

    return 0x4FCFAA;
}