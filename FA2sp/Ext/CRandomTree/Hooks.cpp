#include "Body.h"

#include <Helpers/Macro.h>
#include <CINI.h>

#include "../../FA2sp.h"
#include "../CFinalSunDlg/Body.h"

DEFINE_HOOK(4D4150, CRandomTree_OnInitDialog, 7)
{
    if (ExtConfigs::RandomTerrainObjects)
    {
        GET(CRandomTree*, pThis, ECX);

        pThis->ppmfc::CDialog::OnInitDialog();

        auto&& terrains = Variables::Rules.ParseIndicies("TerrainTypes", true);
        for (size_t i = 0, sz = terrains.size(); i < sz; ++i)
        {
            if (!CViewObjectsExt::IsIgnored(terrains[i]))
                pThis->CLBAvailable.AddString(terrains[i]);
        }

        return 0x4D4865;
    }
    
    return 0;
}