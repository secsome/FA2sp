#include "CTileManager.h"

#include "../../FA2sp.h"
#include "../../Helpers/Translations.h"
#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/MultimapHelper.h"

#include <CLoading.h>

HWND CTileManager::m_hwnd;
CTileSetBrowserFrame* CTileManager::m_parent;
std::vector<std::pair<std::string, std::regex>> CTileManager::Nodes;
std::vector<std::vector<int>> CTileManager::Datas;

void CTileManager::Create(CTileSetBrowserFrame* pWnd)
{
    m_parent = pWnd;
    m_hwnd = CreateDialog(
        static_cast<HINSTANCE>(FA2sp::hInstance),
        MAKEINTRESOURCE(301),
        pWnd->DialogBar.GetSafeHwnd(),
        CTileManager::DlgProc
    );
    if (m_hwnd)
        ShowWindow(m_hwnd, SW_SHOW);
    else
    {
        Logger::Error("Failed to create CTileManager.\n");
        m_parent = NULL;
    }
        
}

void CTileManager::Initialize(HWND& hWnd)
{
    ppmfc::CString buffer;
    if (Translations::GetTranslationItem("TileManagerTitle", buffer))
        SetWindowText(hWnd, buffer);

    HWND hTileTypes = GetDlgItem(hWnd, 6100); 

    InitNodes();

    for (auto& x : CTileManager::Nodes)
        SendMessage(hTileTypes, LB_ADDSTRING, NULL, (LPARAM)x.first.c_str());
    
    UpdateTypes(hWnd);
}

void CTileManager::InitNodes()
{
    CTileManager::Nodes.clear();

    ppmfc::CString lpKey = "TileManagerData";
    lpKey += CLoading::Instance->GetTheaterSuffix();

    MultimapHelper mmh;
    mmh.AddINI(&CINI::FAData);
    auto const pKeys = mmh.ParseIndicies(lpKey);

    for (auto& key : pKeys)
    {
        CTileManager::Nodes.push_back(
            std::make_pair<std::string, std::regex>(key.m_pchData, std::regex(mmh.GetString(lpKey, key), std::regex::icase))
        );
    }

    if (!Translations::GetTranslationItem("TileManagerOthers", lpKey))
        lpKey = "Others";
    
    CTileManager::Nodes.push_back(std::make_pair<std::string, std::regex>(lpKey.m_pchData, std::regex("")));

    CTileManager::Datas.resize(CTileManager::Nodes.size());
}

void CTileManager::Close(HWND& hWnd)
{
    EndDialog(hWnd, NULL);

    CTileManager::m_hwnd = NULL;
    CTileManager::m_parent = NULL;
    CTileManager::Nodes.clear();
    CTileManager::Datas.clear();
}

BOOL CALLBACK CTileManager::DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
    {
        CTileManager::Initialize(hwnd);
        return TRUE;
    }
    case WM_COMMAND:
    {
        WORD ID = LOWORD(wParam);
        WORD CODE = HIWORD(wParam);
        switch (ID)
        {
        case ListBox_Types:
            CTileManager::TypesProc(hwnd, CODE, lParam);
            break;
        case ListBox_Details:
            CTileManager::DetailsProc(hwnd, CODE, lParam);
            break;
        default:
            break;
        }
        break;
    }
    case WM_CLOSE:
    {
        CTileManager::Close(hwnd);
        return TRUE;
    }

    }

    // Process this message through default handler
    return FALSE;
}

void CTileManager::TypesProc(HWND hWnd, WORD nCode, LPARAM lParam)
{
    HWND hListBox = reinterpret_cast<HWND>(lParam);
    if (SendMessage(hListBox, LB_GETCOUNT, NULL, NULL) <= 0)
        return;
    switch (nCode)
    {
    case LBN_SELCHANGE:
    case LBN_DBLCLK:
        UpdateDetails(hWnd, SendMessage(hListBox, LB_GETCURSEL, NULL, NULL));
        break;
    default:
        break;
    }
}

void CTileManager::DetailsProc(HWND hWnd, WORD nCode, LPARAM lParam)
{
    HWND hListBox = reinterpret_cast<HWND>(lParam);
    if (SendMessage(hListBox, LB_GETCOUNT, NULL, NULL) <= 0)
        return;

    HWND hParent = m_parent->DialogBar.GetSafeHwnd();
    HWND hTileComboBox = GetDlgItem(hParent, 1366);

    switch (nCode)
    {
    case LBN_SELCHANGE:
    case LBN_DBLCLK:
        SendMessage(
            hTileComboBox,
            CB_SETCURSEL,

            SendMessage(
                hListBox,
                LB_GETITEMDATA,
                SendMessage(hListBox, LB_GETCURSEL, NULL, NULL),
                NULL
            ),
            NULL
        );
        SendMessage(hParent, WM_COMMAND, MAKEWPARAM(1366, CBN_SELCHANGE), (LPARAM)hTileComboBox);
        break;
    default:
        break;
    }
}

void CTileManager::UpdateTypes(HWND hWnd)
{
    HWND hParent = m_parent->DialogBar.GetSafeHwnd();
    HWND hTileComboBox = GetDlgItem(hParent, 1366);
    int nTileCount = SendMessage(hTileComboBox, CB_GETCOUNT, NULL, NULL);
    if (nTileCount <= 0)
        return;

    ppmfc::CString tile;
    for (int idx = 0; idx < nTileCount; ++idx)
    {
        int nTile = SendMessage(hTileComboBox, CB_GETITEMDATA, idx, NULL);
        tile.Format("TileSet%04d", nTile);
        tile = CINI::CurrentTheater->GetString(tile, "SetName", "NO NAME");
        bool other = true;
        for (size_t i = 0; i < CTileManager::Nodes.size() - 1; ++i)
        {
            if (std::regex_search((std::string)tile.m_pchData, CTileManager::Nodes[i].second))
            {
                CTileManager::Datas[i].push_back(idx); 
                other = false;
            }
        }
        if (other)
            CTileManager::Datas[CTileManager::Nodes.size() - 1].push_back(idx);
    }

    CTileManager::UpdateDetails(hWnd);
}

void CTileManager::UpdateDetails(HWND hWnd, int kNode)
{
    HWND hParent = m_parent->DialogBar.GetSafeHwnd();
    HWND hTileComboBox = GetDlgItem(hParent, 1366);
    HWND hTileDetails = GetDlgItem(hWnd, 6101);
    while (SendMessage(hTileDetails, LB_DELETESTRING, 0, NULL) != LB_ERR);
    if (kNode == -1)
        return;
    else
    {
        ppmfc::CString text, buffer;
        for (auto& x : CTileManager::Datas[kNode])
        {
            int data = SendMessage(hTileComboBox, CB_GETITEMDATA, x, NULL);
            text.Format("TileSet%04d", data);
            text = CINI::CurrentTheater->GetString(text, "SetName", "NO NAME");
            Translations::GetTranslationItem(text, text);
            buffer.Format("(%04d) %s", data, text);
            SendMessage(
                hTileDetails, 
                LB_SETITEMDATA, 
                SendMessage(hTileDetails, LB_ADDSTRING, NULL, (LPARAM)(LPCSTR)buffer), 
                x
            );
        }
    }
    return;
}