#include <Helpers/Macro.h>
#include <Miscs/Miscs.LoadParams.h>
#include <CMapData.h>

#include <algorithm>

#include "Body.h"
#include "../../FA2sp.h"

#include "../CFinalSunDlg/Body.h"

// FA2 Building Property window is fucked
DEFINE_HOOK(417F40, CPropertyBuilding_OnInitDialog, 7)
{
    GET(CPropertyBuilding*, pThis, ECX);

    pThis->ppmfc::CDialog::OnInitDialog();

    CMapData::Instance->UpdateCurrentDocument();

    Miscs::LoadParams::Houses(reinterpret_cast<ppmfc::CComboBox*>(pThis->GetDlgItem(1079)), false, false, false);
    Miscs::LoadParams::Tags(reinterpret_cast<ppmfc::CComboBox*>(pThis->GetDlgItem(1083)), true);

    pThis->CSCStrength.SetRange(0, 256);
    pThis->CSCStrength.SetPos(atoi(pThis->CString_HealthPoint));
    pThis->UpdateData(FALSE);
    
    ppmfc::CComboBox* pUpgrades[3]
    {
        (ppmfc::CComboBox*)pThis->GetDlgItem(1089),
        (ppmfc::CComboBox*)pThis->GetDlgItem(1091),
        (ppmfc::CComboBox*)pThis->GetDlgItem(1092)
    };

    if (CViewObjectsExt::InitPropertyDlgFromProperty)
    {
        pUpgrades[0]->EnableWindow(TRUE);
        pUpgrades[1]->EnableWindow(TRUE);
        pUpgrades[2]->EnableWindow(TRUE);
    }
    else
    {
        for (int i = 1300; i <= 1313; ++i)
            pThis->GetDlgItem(i)->ShowWindow(SW_HIDE);

        int nUpgrades = Variables::Rules.GetInteger(pThis->CString_ObjectID, "Upgrades", 0);

        if (!pThis->CString_ObjectID.IsEmpty())
        {
            nUpgrades = std::clamp(nUpgrades, 0, 3); // no warning pls

            pUpgrades[0]->EnableWindow(nUpgrades > 0);
            pUpgrades[1]->EnableWindow(nUpgrades > 1);
            pUpgrades[2]->EnableWindow(nUpgrades > 2);

            if (nUpgrades > 0)
            {
                std::vector<std::string> upgrades;
                for (auto& bld : CMapData::Instance->BuildingTypes)
                {
                    if (auto const ppString = Variables::Rules.TryGetString(bld.first, "PowersUpBuilding"))
                    {
                        if (*ppString == pThis->CString_ObjectID)
                            upgrades.push_back(bld.first.m_pchData);
                    }
                }
                
                for (const auto& upgrade : upgrades)
                {
                    const auto UIName = CMapData::Instance->GetUIName(upgrade.c_str());
                    const auto name = std::format("{} ({})", upgrade, UIName);

                    for (int i = 0; i < nUpgrades; ++i)
                        pUpgrades[i]->AddString(name.c_str());
                }
            }
        }
    }

    pThis->Translate();

    return 0x41A4AE;
}