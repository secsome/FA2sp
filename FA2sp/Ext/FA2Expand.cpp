#include "FA2Expand.h"

#include "CAITriggerTypes/Body.h"
#include "CAITriggerTypesEnable/Body.h"
#include "CBasic/Body.h"
#include "CCellTag/Body.h"
#include "CChangeMapSize/Body.h"
#include "CCreateMap1/Body.h"
#include "CCreateMap2/Body.h"
#include "CCreateMap3A/Body.h"
#include "CCreateMap3B/Body.h"
#include "CCreateMap4/Body.h"
#include "CCredits/Body.h"
#include "CDialog289/Body.h"
#include "CEasterEgg/Body.h"
#include "CHouses/Body.h"
#include "CINIEditor/Body.h"
#include "CINIEditorImport/Body.h"
#include "CLighting/Body.h"
#include "CLoading/Body.h"
#include "CLoadingGraphics/Body.h"
#include "CLocal/Body.h"
#include "CMapD/Body.h"
#include "CMapScripts/Body.h"
#include "CMinimap/Body.h"
#include "CMMX/Body.h"
#include "CNewHouse/Body.h"
#include "COptions/Body.h"
#include "CPropertyAircraft/Body.h"
#include "CPropertyBuilding/Body.h"
#include "CPropertyInfantry/Body.h"
#include "CPropertyUnit/Body.h"
#include "CRandomTree/Body.h"
#include "CSaveOption/Body.h"
#include "CScriptTypes/Body.h"
#include "CSearchWaypoint/Body.h"
#include "CSingleplayerSettings/Body.h"
#include "CSpecialFlags/Body.h"
#include "CTags/Body.h"
#include "CTaskforce/Body.h"
#include "CTeamTypes/Body.h"
#include "CTileSetBrowserFrame/Body.h"
#include "CTileSetBrowserView/Body.h"
#include "CTriggerAction/Body.h"
#include "CTriggerEvent/Body.h"
#include "CTriggerFrame/Body.h"
#include "CTriggerOption/Body.h"
#include "CUpdateProgress/Body.h"
#include "CFinalSunDlg/Body.h"
#include "CIsoView/Body.h"
//
//#include <CMixFile.h>

void __stdcall FA2Expand::ExeRun()
{
    //CLoadingExt::ProgramStartupInit();
    //CLoadingGraphicsExt::ProgramStartupInit();
    //CUpdateProgressExt::ProgramStartupInit();
    //
    //CTileSetBrowserViewExt::ProgramStartupInit();
    CTileSetBrowserFrameExt::ProgramStartupInit();
    //
    //CCreateMap1Ext::ProgramStartupInit();
    //CCreateMap2Ext::ProgramStartupInit();
    //CCreateMap3AExt::ProgramStartupInit();
    //CCreateMap3BExt::ProgramStartupInit();
    //CCreateMap4Ext::ProgramStartupInit();
    //
    CTriggerFrameExt::ProgramStartupInit();
    CTriggerOptionExt::ProgramStartupInit();
    CTriggerEventExt::ProgramStartupInit();
    CTriggerActionExt::ProgramStartupInit();
    //CTagsExt::ProgramStartupInit();
    CTaskForceExt::ProgramStartupInit();
    CScriptTypesExt::ProgramStartupInit();
    CTeamTypesExt::ProgramStartupInit();
    //CAITriggerTypesExt::ProgramStartupInit();
    //CAITriggerTypesEnableExt::ProgramStartupInit();
    //CLocalExt::ProgramStartupInit();
    //CINIEditorExt::ProgramStartupInit();
    //CINIEditorImportExt::ProgramStartupInit();
    //CHousesExt::ProgramStartupInit();
    //CNewHouseExt::ProgramStartupInit();
    //CBasicExt::ProgramStartupInit();
    //CMapDExt::ProgramStartupInit();
    //CChangeMapSizeExt::ProgramStartupInit();
    //CSingleplayerSettingsExt::ProgramStartupInit();
    //CSpecialFlagsExt::ProgramStartupInit();
    //CLightingExt::ProgramStartupInit();
    //
    //CSearchWaypointExt::ProgramStartupInit();
    //CCellTagExt::ProgramStartupInit();
    //CRandomTreeExt::ProgramStartupInit();
    //CPropertyInfantryExt::ProgramStartupInit();
    //CPropertyAircraftExt::ProgramStartupInit();
    //CPropertyBuildingExt::ProgramStartupInit();
    //CPropertyUnitExt::ProgramStartupInit();
    //
    //CMinimapExt::ProgramStartupInit();
    //COptionsExt::ProgramStartupInit();
    //CCreditsExt::ProgramStartupInit();
    //CEasterEggExt::ProgramStartupInit();
    //
    //CMapScriptsExt::ProgramStartupInit();
    //CSaveOptionExt::ProgramStartupInit();
    //CMMXExt::ProgramStartupInit();
    //
    //CDialog289Ext::ProgramStartupInit();
    //CFinalSunDlgExt::ProgramStartupInit();
    //CIsoViewExt::ProgramStartupInit();

    /*auto ReplaceOnInitDialog = [](auto pOnInitDialogExt, DWORD dwOrigin) {
        auto address = pOnInitDialogExt;
        RunTime::ResetMemoryContentAt(dwOrigin, &address, 4);
    };*/

    //ReplaceOnInitDialog(&CTaskForceExt::OnInitDialog, 0x596CB4);


}

FA2Expand::FA2Expand()
{

}


FA2Expand::~FA2Expand()
{

}