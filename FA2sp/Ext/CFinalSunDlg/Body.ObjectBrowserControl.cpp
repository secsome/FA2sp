#include "Body.h"

#include "../../Helpers/Translations.h"
#include "../../Helpers/STDHelpers.h"

#include "../../Miscs/TheaterInfo.h"

#include "../../FA2sp.h"

#include <CINI.h>
#include <CMapData.h>
#include <CIsoView.h>
#include <CTileTypeClass.h>

std::array<HTREEITEM, CViewObjectsExt::Root_Count> CViewObjectsExt::ExtNodes;
std::set<ppmfc::CString> CViewObjectsExt::IgnoreSet;
std::set<ppmfc::CString> CViewObjectsExt::ForceName;
std::set<ppmfc::CString> CViewObjectsExt::ExtSets[Set_Count];
std::map<ppmfc::CString, int> CViewObjectsExt::KnownItem;
std::map<ppmfc::CString, int> CViewObjectsExt::Owners;

std::unique_ptr<CPropertyBuilding> CViewObjectsExt::BuildingBrushDlg;
std::unique_ptr<CPropertyInfantry> CViewObjectsExt::InfantryBrushDlg;
std::unique_ptr<CPropertyUnit> CViewObjectsExt::VehicleBrushDlg;
std::unique_ptr<CPropertyAircraft> CViewObjectsExt::AircraftBrushDlg;
bool CViewObjectsExt::BuildingBrushBools[14];
bool CViewObjectsExt::InfantryBrushBools[10];
bool CViewObjectsExt::VehicleBrushBools[11];
bool CViewObjectsExt::AircraftBrushBools[9];
bool CViewObjectsExt::InitPropertyDlgFromProperty{ false };

HTREEITEM CViewObjectsExt::InsertString(const char* pString, DWORD dwItemData,
    HTREEITEM hParent, HTREEITEM hInsertAfter)
{
    return this->GetTreeCtrl().InsertItem(TVIF_TEXT | TVIF_PARAM, pString, 0, 0, 0, 0, dwItemData, hParent, hInsertAfter);
}

HTREEITEM CViewObjectsExt::InsertTranslatedString(const char* pOriginString, DWORD dwItemData,
    HTREEITEM hParent, HTREEITEM hInsertAfter)
{
    ppmfc::CString buffer;
    bool result = Translations::GetTranslationItem(pOriginString, buffer);
    return InsertString(result ? buffer : pOriginString, dwItemData, hParent, hInsertAfter);
}

ppmfc::CString CViewObjectsExt::QueryUIName(const char* pRegName, bool bOnlyOneLine)
{
    if (!bOnlyOneLine)
    {
        if (ForceName.find(pRegName) != ForceName.end())
            return Variables::Rules.GetString(pRegName, "Name", pRegName);
        else
            return CMapData::GetUIName(pRegName);
    }
    
    ppmfc::CString buffer;

    if (ForceName.find(pRegName) != ForceName.end())
        buffer = Variables::Rules.GetString(pRegName, "Name", pRegName);
    else
        buffer = CMapData::GetUIName(pRegName);

    int idx = buffer.Find('\n');
    return idx == -1 ? buffer : buffer.Mid(0, idx);
}

void CViewObjectsExt::Redraw()
{
    Redraw_Initialize();
    Redraw_MainList();
    Redraw_Ground();
    Redraw_Owner();
    Redraw_Infantry();
    Redraw_Vehicle();
    Redraw_Aircraft();
    Redraw_Building();
    Redraw_Terrain();
    Redraw_Smudge();
    Redraw_Overlay();
    Redraw_Waypoint();
    Redraw_Celltag();
    Redraw_Basenode();
    Redraw_Tunnel();
    Redraw_PlayerLocation(); // player location is just waypoints!
    Redraw_PropertyBrush();
}

void CViewObjectsExt::Redraw_Initialize()
{
    for (auto root : ExtNodes)
        root = NULL;
    KnownItem.clear();
    IgnoreSet.clear();
    ForceName.clear();
    Owners.clear();
    this->GetTreeCtrl().DeleteAllItems();

    auto& rules = CINI::Rules();
    auto& fadata = CINI::FAData();
    auto& doc = CINI::CurrentDocument();

    auto loadSet = [](const char* pTypeName, int nType)
    {
        ExtSets[nType].clear();
        auto& section = Variables::Rules.GetSection(pTypeName);
        for (auto& itr : section)
            ExtSets[nType].insert(itr.second);
    };

    loadSet("BuildingTypes", Set_Building);
    loadSet("InfantryTypes", Set_Infantry);
    loadSet("VehicleTypes", Set_Vehicle);
    loadSet("AircraftTypes", Set_Aircraft);

    if (ExtConfigs::BrowserRedraw_GuessMode == 1)
    {
        auto loadOwner = []()
        {
            auto& sides = Variables::Rules.ParseIndicies("Sides", true);
            for (size_t i = 0, sz = sides.size(); i < sz; ++i)
                for (auto& owner : STDHelpers::SplitString(sides[i]))
                    Owners[owner] = i;
        };
        loadOwner();
    }

    if (auto knownSection = fadata.GetSection("ForceSides"))
    {
        for (auto& item : knownSection->GetEntities())
        {
            int sideIndex = STDHelpers::ParseToInt(item.second, -1);
            if (sideIndex >= fadata.GetKeyCount("Sides"))
                continue;
            if (sideIndex < -1)
                sideIndex = -1;
            KnownItem[item.first] = sideIndex;
        }
    }

    if (auto ignores = fadata.GetSection("IgnoreRA2"))
        for (auto& item : ignores->GetEntities())
        {
            ppmfc::CString tmp = item.second;
            tmp.Trim();
            IgnoreSet.insert(tmp);
        }

    if (auto forcenames = fadata.GetSection("ForceName"))
        for (auto& item : forcenames->GetEntities())
        {
            ppmfc::CString tmp = item.second;
            tmp.Trim();
            ForceName.insert(tmp);
        }

}

void CViewObjectsExt::Redraw_MainList()
{
    ExtNodes[Root_Nothing] = this->InsertTranslatedString("NothingObList", -2);
    ExtNodes[Root_Ground] = this->InsertTranslatedString("GroundObList", 13);
    ExtNodes[Root_Owner] = this->InsertTranslatedString("ChangeOwnerObList");
    ExtNodes[Root_Infantry] = this->InsertTranslatedString("InfantryObList", 0);
    ExtNodes[Root_Vehicle] = this->InsertTranslatedString("VehiclesObList", 1);
    ExtNodes[Root_Aircraft] = this->InsertTranslatedString("AircraftObList", 2);
    ExtNodes[Root_Building] = this->InsertTranslatedString("StructuresObList", 3);
    ExtNodes[Root_Terrain] = this->InsertTranslatedString("TerrainObList", 4);
    ExtNodes[Root_Smudge] = this->InsertTranslatedString("SmudgesObList", 10);
    ExtNodes[Root_Overlay] = this->InsertTranslatedString("OverlayObList", 5);
    ExtNodes[Root_Waypoint] = this->InsertTranslatedString("WaypointsObList", 6);
    ExtNodes[Root_Celltag] = this->InsertTranslatedString("CelltagsObList", 7);
    ExtNodes[Root_Basenode] = this->InsertTranslatedString("BaseNodesObList", 8);
    ExtNodes[Root_Tunnel] = this->InsertTranslatedString("TunnelObList", 9);
    ExtNodes[Root_PlayerLocation] = this->InsertTranslatedString("StartpointsObList", 12);
    ExtNodes[Root_PropertyBrush] = this->InsertTranslatedString("PropertyBrushObList", 14);
    ExtNodes[Root_Delete] = this->InsertTranslatedString("DelObjObList", 10);
}

void CViewObjectsExt::Redraw_Ground()
{
    HTREEITEM& hGround = ExtNodes[Root_Ground];
    if (hGround == NULL)    return;

    auto& doc = CINI::CurrentDocument();
    CString theater = doc.GetString("Map", "Theater");
    if (theater == "NEWURBAN")
        theater = "UBN";

    CString suffix;
    if (theater != "")
        suffix = theater.Mid(0, 3);

    this->InsertTranslatedString("GroundClearObList" + suffix, 61, hGround);
    this->InsertTranslatedString("GroundSandObList"  + suffix, 62, hGround);
    this->InsertTranslatedString("GroundRoughObList" + suffix, 63, hGround);
    this->InsertTranslatedString("GroundGreenObList" + suffix, 65, hGround);
    this->InsertTranslatedString("GroundPaveObList"  + suffix, 66, hGround);
    this->InsertTranslatedString("GroundWaterObList", 64, hGround);

    if (CINI::CurrentTheater)
    {
        int i = 67;
        for (auto& morphables : TheaterInfo::CurrentInfo)
        {
            auto InsertTile = [&](int nTileset)
            {
                FA2sp::Buffer.Format("TileSet%04d", nTileset);
                FA2sp::Buffer = CINI::CurrentTheater->GetString(FA2sp::Buffer, "SetName", FA2sp::Buffer);
                ppmfc::CString buffer;
                Translations::GetTranslationItem(FA2sp::Buffer, FA2sp::Buffer);
                return this->InsertString(FA2sp::Buffer, i++, hGround, TVI_LAST);
            };

            InsertTile(morphables.Morphable);
        }
    }
}

void CViewObjectsExt::Redraw_Owner()
{
    HTREEITEM& hOwner = ExtNodes[Root_Owner];
    if (hOwner == NULL)    return;

    if (ExtConfigs::BrowserRedraw_SafeHouses)
    {
        if (CMapData::Instance->IsMultiOnly())
        {
            auto& section = Variables::Rules.GetSection("Countries");
            auto itr = section.begin();
            for (size_t i = 0, sz = section.size(); i < sz; ++i, ++itr)
                if (strcmp(itr->second, "Neutral") == 0 || strcmp(itr->second, "Special") == 0)
                    this->InsertString(itr->second, Const_House + i, hOwner);
        }
        else
        {
            auto& section = Variables::Rules.ParseIndicies("Houses", true);
            for (size_t i = 0, sz = section.size(); i < sz; ++i)
                this->InsertString(section[i], Const_House + i, hOwner);
        }
    }
    else
    {
        if (CMapData::Instance->IsMultiOnly())
        {
            if (auto pSection = CINI::Rules->GetSection("Countries"))
            {
                auto& section = pSection->GetEntities();
                size_t i = 0;
                for (auto& itr : section)
                    this->InsertString(itr.second, Const_House + i++, hOwner);
            }
        }
        else
        {
            if (auto pSection = CINI::CurrentDocument->GetSection("Houses"))
            {
                auto& section = pSection->GetEntities();
                size_t i = 0;
                for (auto& itr : section)
                    this->InsertString(itr.second, Const_House + i++, hOwner);
            }
        }
    }
}

void CViewObjectsExt::Redraw_Infantry()
{
    HTREEITEM& hInfantry = ExtNodes[Root_Infantry];
    if (hInfantry == NULL)   return;

    std::map<int, HTREEITEM> subNodes;

    auto& fadata = CINI::FAData();

    int i = 0;
    if (auto sides = fadata.GetSection("Sides"))
        for (auto& itr : sides->GetEntities())
            subNodes[i++] = this->InsertString(itr.second, -1, hInfantry);
    else
    {
        subNodes[i++] = this->InsertString("Allied", -1, hInfantry);
        subNodes[i++] = this->InsertString("Soviet", -1, hInfantry);
        subNodes[i++] = this->InsertString("Yuri", -1, hInfantry);
    }
    subNodes[-1] = this->InsertTranslatedString("OthObList", -1, hInfantry);

    auto& infantries = Variables::Rules.GetSection("InfantryTypes");
    for (auto& inf : infantries)
    {
        if (IgnoreSet.find(inf.second) != IgnoreSet.end())
            continue;
        int index = STDHelpers::ParseToInt(inf.first, -1);
        if (index == -1)   continue;
        int side = GuessSide(inf.second, Set_Infantry);
        if (subNodes.find(side) == subNodes.end())
            side = -1;
        this->InsertString(
            QueryUIName(inf.second) + " (" + inf.second + ")",
            Const_Infantry + index,
            subNodes[side]
        );
    }

    // Clear up
    if (ExtConfigs::BrowserRedraw_CleanUp)
    {
        for (auto& subnode : subNodes)
        {
            if (!this->GetTreeCtrl().ItemHasChildren(subnode.second))
                this->GetTreeCtrl().DeleteItem(subnode.second);
        }
    }
}

void CViewObjectsExt::Redraw_Vehicle()
{
    HTREEITEM& hVehicle = ExtNodes[Root_Vehicle];
    if (hVehicle == NULL)   return;

    std::map<int, HTREEITEM> subNodes;

    auto& fadata = CINI::FAData();

    int i = 0;
    if (auto sides = fadata.GetSection("Sides"))
        for (auto& itr : sides->GetEntities())
            subNodes[i++] = this->InsertString(itr.second, -1, hVehicle);
    else
    {
        subNodes[i++] = this->InsertString("Allied", -1, hVehicle);
        subNodes[i++] = this->InsertString("Soviet", -1, hVehicle);
        subNodes[i++] = this->InsertString("Yuri", -1, hVehicle);
    }
    subNodes[-1] = this->InsertTranslatedString("OthObList", -1, hVehicle);

    auto& vehicles = Variables::Rules.GetSection("VehicleTypes");
    for (auto& veh : vehicles)
    {
        if (IgnoreSet.find(veh.second) != IgnoreSet.end())
            continue;
        int index = STDHelpers::ParseToInt(veh.first, -1);
        if (index == -1)   continue;
        int side = GuessSide(veh.second, Set_Vehicle);
        if (subNodes.find(side) == subNodes.end())
            side = -1;
        this->InsertString(
            QueryUIName(veh.second) + " (" + veh.second + ")",
            Const_Vehicle + index,
            subNodes[side]
        );
    }

    // Clear up
    if (ExtConfigs::BrowserRedraw_CleanUp)
    {
        for (auto& subnode : subNodes)
        {
            if (!this->GetTreeCtrl().ItemHasChildren(subnode.second))
                this->GetTreeCtrl().DeleteItem(subnode.second);
        }
    }
}

void CViewObjectsExt::Redraw_Aircraft()
{
    HTREEITEM& hAircraft = ExtNodes[Root_Aircraft];
    if (hAircraft == NULL)   return;

    std::map<int, HTREEITEM> subNodes;

    auto& rules = CINI::Rules();
    auto& fadata = CINI::FAData();

    int i = 0;
    if (auto sides = fadata.GetSection("Sides"))
        for (auto& itr : sides->GetEntities())
            subNodes[i++] = this->InsertString(itr.second, -1, hAircraft);
    else
    {
        subNodes[i++] = this->InsertString("Allied", -1, hAircraft);
        subNodes[i++] = this->InsertString("Soviet", -1, hAircraft);
        subNodes[i++] = this->InsertString("Yuri", -1, hAircraft);
    }
    subNodes[-1] = this->InsertTranslatedString("OthObList", -1, hAircraft);

    auto& aircrafts = Variables::Rules.GetSection("AircraftTypes");
    for (auto& air : aircrafts)
    {
        if (IgnoreSet.find(air.second) != IgnoreSet.end())
            continue;
        int index = STDHelpers::ParseToInt(air.first, -1);
        if (index == -1)   continue;
        int side = GuessSide(air.second, Set_Aircraft);
        if (subNodes.find(side) == subNodes.end())
            side = -1;
        this->InsertString(
            QueryUIName(air.second) + " (" + air.second + ")",
            Const_Aircraft + index,
            subNodes[side]
        );
    }

    // Clear up
    if (ExtConfigs::BrowserRedraw_CleanUp)
    {
        for (auto& subnode : subNodes)
        {
            if (!this->GetTreeCtrl().ItemHasChildren(subnode.second))
                this->GetTreeCtrl().DeleteItem(subnode.second);
        }
    }
}

void CViewObjectsExt::Redraw_Building()
{
    HTREEITEM& hBuilding = ExtNodes[Root_Building];
    if (hBuilding == NULL)   return;

    std::map<int, HTREEITEM> subNodes;

    auto& rules = CINI::Rules();
    auto& fadata = CINI::FAData();

    int i = 0;
    if (auto sides = fadata.GetSection("Sides"))
        for (auto& itr : sides->GetEntities())
            subNodes[i++] = this->InsertString(itr.second, -1, hBuilding);
    else
    {
        subNodes[i++] = this->InsertString("Allied", -1, hBuilding);
        subNodes[i++] = this->InsertString("Soviet", -1, hBuilding);
        subNodes[i++] = this->InsertString("Yuri", -1, hBuilding);
    }
    subNodes[-1] = this->InsertTranslatedString("OthObList", -1, hBuilding);

    auto& buildings = Variables::Rules.GetSection("BuildingTypes");
    for (auto& bud : buildings)
    {
        if (IgnoreSet.find(bud.second) != IgnoreSet.end())
            continue;
        int index = STDHelpers::ParseToInt(bud.first, -1);
        if (index == -1)   continue;
        int side = GuessSide(bud.second, Set_Building);
        if (subNodes.find(side) == subNodes.end())
            side = -1;
        this->InsertString(
            QueryUIName(bud.second) + " (" + bud.second + ")",
            Const_Building + index,
            subNodes[side]
        );
    }

    // Clear up
    if (ExtConfigs::BrowserRedraw_CleanUp)
    {
        for (auto& subnode : subNodes)
        {
            if (!this->GetTreeCtrl().ItemHasChildren(subnode.second))
                this->GetTreeCtrl().DeleteItem(subnode.second);
        }
    }
}

void CViewObjectsExt::Redraw_Terrain()
{
    HTREEITEM& hTerrain = ExtNodes[Root_Terrain];
    if (hTerrain == NULL)   return;

    std::vector<std::pair<HTREEITEM, ppmfc::CString>> nodes;

    if (auto pSection = CINI::FAData->GetSection("ObjectBrowser.TerrainTypes"))
    {
        std::map<int, ppmfc::CString> collector;

        for (auto& pair : pSection->GetIndices())
            collector[pair.second] = pair.first;

        for (auto& pair : collector)
        {
            const auto& contains = pair.second;
            const auto translation = pSection->GetEntities().find(contains)->second;

            nodes.push_back(std::make_pair(this->InsertTranslatedString(translation, -1, hTerrain), contains));
        }
    }
    HTREEITEM hOther = this->InsertTranslatedString("OthObList", -1, hTerrain);

    auto& terrains = Variables::Rules.ParseIndicies("TerrainTypes", true);
    for (size_t i = 0, sz = terrains.size(); i < sz; ++i)
    {
        if (IgnoreSet.find(terrains[i]) == IgnoreSet.end())
        {
            FA2sp::Buffer = QueryUIName(terrains[i]);
            FA2sp::Buffer += " (" + terrains[i] + ")";
            bool bNotOther = false;
            for (const auto& node : nodes)
            {
                if (terrains[i].Find(node.second) >= 0)
                {
                    this->InsertString(FA2sp::Buffer, Const_Terrain + i, node.first);
                    bNotOther = true;
                }
            }
            if (!bNotOther)
                this->InsertString(FA2sp::Buffer, Const_Terrain + i, hOther);
        }
    }

    this->InsertTranslatedString("RndTreeObList", 50999, hTerrain);
}

void CViewObjectsExt::Redraw_Smudge()
{
    HTREEITEM& hSmudge = ExtNodes[Root_Smudge];
    if (hSmudge == NULL)   return;

    std::vector<std::pair<HTREEITEM, ppmfc::CString>> nodes;

    if (auto pSection = CINI::FAData->GetSection("ObjectBrowser.SmudgeTypes"))
    {
        std::map<int, ppmfc::CString> collector;

        for (auto& pair : pSection->GetIndices())
            collector[pair.second] = pair.first;

        for (auto& pair : collector)
        {
            const auto& contains = pair.second;
            const auto translation = pSection->GetEntities().find(contains)->second;

            nodes.push_back(std::make_pair(this->InsertTranslatedString(translation, -1, hSmudge), contains));
        }
    }
    HTREEITEM hOther = this->InsertTranslatedString("OthObList", -1, hSmudge);

    auto& smudges = Variables::Rules.ParseIndicies("SmudgeTypes", true);
    for (size_t i = 0, sz = smudges.size(); i < sz; ++i)
    {
        if (IgnoreSet.find(smudges[i]) == IgnoreSet.end())
        {
            bool bNotOther = false;
            for (const auto& node : nodes)
            {
                if (smudges[i].Find(node.second) >= 0)
                {
                    this->InsertString(smudges[i], Const_Smudge + i, node.first);
                    bNotOther = true;
                }
            }
            if (!bNotOther)
                this->InsertString(smudges[i], Const_Smudge + i, hOther);
        }
    }
}

void CViewObjectsExt::Redraw_Overlay()
{
    HTREEITEM& hOverlay = ExtNodes[Root_Overlay];
    if (hOverlay == NULL)   return;

    auto& rules = CINI::Rules();

    HTREEITEM hTemp;
    hTemp = this->InsertTranslatedString("DelOvrlObList", -1, hOverlay);
    this->InsertTranslatedString("DelOvrl0ObList", 60100, hTemp);
    this->InsertTranslatedString("DelOvrl1ObList", 60101, hTemp);
    this->InsertTranslatedString("DelOvrl2ObList", 60102, hTemp);
    this->InsertTranslatedString("DelOvrl3ObList", 60103, hTemp);

    hTemp = this->InsertTranslatedString("GrTibObList", -1, hOverlay);
    this->InsertTranslatedString("DrawTibObList", 60210, hTemp);
    this->InsertTranslatedString("DrawTib2ObList", 60310, hTemp);

    hTemp = this->InsertTranslatedString("BridgesObList", -1, hOverlay);
    this->InsertTranslatedString("BigBridgeObList", 60500, hTemp);
    this->InsertTranslatedString("SmallBridgeObList", 60501, hTemp);
    this->InsertTranslatedString("BigTrackBridgeObList", 60502, hTemp);
    this->InsertTranslatedString("SmallConcreteBridgeObList", 60503, hTemp);

    // Walls
    HTREEITEM hWalls = this->InsertTranslatedString("OthObList", -1, hOverlay);

    hTemp = this->InsertTranslatedString("AllObList", -1, hOverlay);

    this->InsertTranslatedString("OvrlManuallyObList", 60001, hOverlay);
    this->InsertTranslatedString("OvrlDataManuallyObList", 60002, hOverlay);

    if (!rules.SectionExists("OverlayTypes"))
        return;

    // a rough support for tracks
    this->InsertTranslatedString("Tracks", Const_Overlay + 39, hOverlay);
    
    MultimapHelper mmh;
    mmh.AddINI(&CINI::Rules());
    auto& overlays = mmh.ParseIndicies("OverlayTypes", true);
    for (size_t i = 0, sz = std::min<unsigned int>(overlays.size(), 255); i < sz; ++i)
    {
        CString buffer;
        buffer = QueryUIName(overlays[i]);
        buffer += " (" + overlays[i] + ")";
        if (rules.GetBool(overlays[i], "Wall"))
            this->InsertString(
                QueryUIName(overlays[i]),
                Const_Overlay + i,
                hWalls
            );
        if (IgnoreSet.find(overlays[i]) == IgnoreSet.end())
            this->InsertString(buffer, Const_Overlay + i, hTemp);
    }
}

void CViewObjectsExt::Redraw_Waypoint()
{
    HTREEITEM& hWaypoint = ExtNodes[Root_Waypoint];
    if (hWaypoint == NULL)   return;

    this->InsertTranslatedString("CreateWaypObList", 20, hWaypoint);
    this->InsertTranslatedString("DelWaypObList", 21, hWaypoint);
    this->InsertTranslatedString("CreateSpecWaypObList", 22, hWaypoint);
}

void CViewObjectsExt::Redraw_Celltag()
{
    HTREEITEM& hCellTag = ExtNodes[Root_Celltag];
    if (hCellTag == NULL)   return;

    this->InsertTranslatedString("CreateCelltagObList", 36, hCellTag);
    this->InsertTranslatedString("DelCelltagObList", 37, hCellTag);
    this->InsertTranslatedString("CelltagPropObList", 38, hCellTag);
}

void CViewObjectsExt::Redraw_Basenode()
{
    HTREEITEM& hBasenode = ExtNodes[Root_Basenode];
    if (hBasenode == NULL)   return;

    this->InsertTranslatedString("CreateNodeNoDelObList", 40, hBasenode);
    this->InsertTranslatedString("CreateNodeDelObList", 41, hBasenode);
    this->InsertTranslatedString("DelNodeObList", 42, hBasenode);
}

void CViewObjectsExt::Redraw_Tunnel()
{
    HTREEITEM& hTunnel = ExtNodes[Root_Tunnel];
    if (hTunnel == NULL)   return;

    if (CINI::FAData->GetBool("Debug", "AllowTunnels"))
    {
        this->InsertTranslatedString("NewTunnelObList", 50, hTunnel);
        this->InsertTranslatedString("DelTunnelObList", 51, hTunnel);
    }
}

void CViewObjectsExt::Redraw_PlayerLocation()
{
    HTREEITEM& hPlayerLocation = ExtNodes[Root_PlayerLocation];
    if (hPlayerLocation == NULL)   return;

    this->InsertTranslatedString("StartpointsDelete", 21, hPlayerLocation);

    if (CMapData::Instance->IsMultiOnly())
    {
        for (int i = 0; i < 8; ++i)
        {
            FA2sp::Buffer.Format("Player %d", i);
            this->InsertString(FA2sp::Buffer, 23 + i, hPlayerLocation);
        }
    }
}

void CViewObjectsExt::Redraw_PropertyBrush()
{
    HTREEITEM& hPropertyBrush = ExtNodes[Root_PropertyBrush];
    if (hPropertyBrush == NULL)    return;

    this->InsertTranslatedString("PropertyBrushBuilding", Const_PropertyBrush + Set_Building, hPropertyBrush);
    this->InsertTranslatedString("PropertyBrushInfantry", Const_PropertyBrush + Set_Infantry, hPropertyBrush);
    this->InsertTranslatedString("PropertyBrushVehicle", Const_PropertyBrush + Set_Vehicle, hPropertyBrush);
    this->InsertTranslatedString("PropertyBrushAircraft", Const_PropertyBrush + Set_Aircraft, hPropertyBrush);
}

bool CViewObjectsExt::DoPropertyBrush_Building()
{
    if (this->BuildingBrushDlg.get() == nullptr)
        this->BuildingBrushDlg = std::make_unique<CPropertyBuilding>(CFinalSunDlg::Instance->MyViewFrame.pIsoView);

    for (auto& v : this->BuildingBrushBools)
        v = false;

    return this->BuildingBrushDlg->ppmfc::CDialog::DoModal() == IDOK;
}

bool CViewObjectsExt::DoPropertyBrush_Aircraft()
{
    if (this->AircraftBrushDlg.get() == nullptr)
        this->AircraftBrushDlg = std::make_unique<CPropertyAircraft>(CFinalSunDlg::Instance->MyViewFrame.pIsoView);

    for (auto& v : this->AircraftBrushBools)
        v = false;

    return this->AircraftBrushDlg->ppmfc::CDialog::DoModal() == IDOK;
}

bool CViewObjectsExt::DoPropertyBrush_Vehicle()
{
    if (this->VehicleBrushDlg.get() == nullptr)
        this->VehicleBrushDlg = std::make_unique<CPropertyUnit>(CFinalSunDlg::Instance->MyViewFrame.pIsoView);

    for (auto& v : this->VehicleBrushBools)
        v = false;

    return this->VehicleBrushDlg->ppmfc::CDialog::DoModal() == IDOK;
}

bool CViewObjectsExt::DoPropertyBrush_Infantry()
{
    if (this->InfantryBrushDlg.get() == nullptr)
        this->InfantryBrushDlg = std::make_unique<CPropertyInfantry>(CFinalSunDlg::Instance->MyViewFrame.pIsoView);

    for (auto& v : this->InfantryBrushBools)
        v = false;

    return this->InfantryBrushDlg->ppmfc::CDialog::DoModal() == IDOK;
}

void CViewObjectsExt::ApplyPropertyBrush(int X, int Y)
{
    int nIndex = CMapData::Instance->GetCoordIndex(X, Y);
    const auto& CellData = CMapData::Instance->CellDatas[nIndex];

    if (CIsoView::CurrentCommand->Type == Set_Building)
    {
        if (CellData.Structure != -1)
            ApplyPropertyBrush_Building(CellData.Structure);
    }
    else if (CIsoView::CurrentCommand->Type == Set_Infantry)
    {
        if (CellData.Infantry[0] != -1)
            ApplyPropertyBrush_Infantry(CellData.Infantry[0]);
        if (CellData.Infantry[1] != -1)
            ApplyPropertyBrush_Infantry(CellData.Infantry[1]);
        if (CellData.Infantry[2] != -1)
            ApplyPropertyBrush_Infantry(CellData.Infantry[2]);
    }
    else if (CIsoView::CurrentCommand->Type == Set_Vehicle)
    {
        if (CellData.Unit != -1)
            ApplyPropertyBrush_Vehicle(CellData.Unit);
    }
    else if (CIsoView::CurrentCommand->Type == Set_Aircraft)
    {
        if (CellData.Aircraft != -1)
            ApplyPropertyBrush_Aircraft(CellData.Aircraft);
    }
}

void CViewObjectsExt::ApplyPropertyBrush_Building(int nIndex)
{
    CBuildingData data;
    CMapData::Instance->GetBuildingData(nIndex, data);
    
    ApplyPropertyBrush_Building(data);

    CMapData::Instance->DeleteBuildingData(nIndex);
    CMapData::Instance->SetBuildingData(&data, nullptr, nullptr, 0, "");

    ::RedrawWindow(CFinalSunDlg::Instance->MyViewFrame.pIsoView->m_hWnd, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE);
}

void CViewObjectsExt::ApplyPropertyBrush_Infantry(int nIndex)
{
    CInfantryData data;
    CMapData::Instance->GetInfantryData(nIndex, data);

    ApplyPropertyBrush_Infantry(data);

    CMapData::Instance->DeleteInfantryData(nIndex);
    CMapData::Instance->SetInfantryData(&data, nullptr, nullptr, 0, -1);

    ::RedrawWindow(CFinalSunDlg::Instance->MyViewFrame.pIsoView->m_hWnd, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE);
}

void CViewObjectsExt::ApplyPropertyBrush_Aircraft(int nIndex)
{
    CAircraftData data;
    CMapData::Instance->GetAircraftData(nIndex, data);

    ApplyPropertyBrush_Aircraft(data);

    CMapData::Instance->DeleteAircraftData(nIndex);
    CMapData::Instance->SetAircraftData(&data, nullptr, nullptr, 0, "");

    ::RedrawWindow(CFinalSunDlg::Instance->MyViewFrame.pIsoView->m_hWnd, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE);
}

void CViewObjectsExt::ApplyPropertyBrush_Vehicle(int nIndex)
{
    CUnitData data;
    CMapData::Instance->GetUnitData(nIndex, data);

    ApplyPropertyBrush_Vehicle(data);

    CMapData::Instance->DeleteUnitData(nIndex);
    CMapData::Instance->SetUnitData(&data, nullptr, nullptr, 0, "");

    ::RedrawWindow(CFinalSunDlg::Instance->MyViewFrame.pIsoView->m_hWnd, 0, 0, RDW_UPDATENOW | RDW_INVALIDATE);
}

void CViewObjectsExt::ApplyPropertyBrush_Building(CBuildingData& data)
{
    if (!BuildingBrushDlg)
        return;

    auto ApplyValue = [&](int nCheckBoxIdx, ppmfc::CString& src, ppmfc::CString& dst)
    {
        if (BuildingBrushBools[nCheckBoxIdx - 1300])
        {
            if (!src.IsEmpty())
                dst = src;
        }
    };

    ApplyValue(1300, BuildingBrushDlg->CString_House, data.House);
    ApplyValue(1301, BuildingBrushDlg->CString_HealthPoint, data.Health);
    ApplyValue(1302, BuildingBrushDlg->CString_Direction, data.Facing);
    ApplyValue(1303, BuildingBrushDlg->CString_Sellable, data.AISellable);
    ApplyValue(1304, BuildingBrushDlg->CString_Rebuildable, data.AIRebuildable);
    ApplyValue(1305, BuildingBrushDlg->CString_EnergySupport, data.PoweredOn);
    ApplyValue(1306, BuildingBrushDlg->CString_UpgradeCount, data.Upgrades);
    ApplyValue(1307, BuildingBrushDlg->CString_Spotlight, data.SpotLight);
    ApplyValue(1308, BuildingBrushDlg->CString_Upgrade1, data.Upgrade1);
    ApplyValue(1309, BuildingBrushDlg->CString_Upgrade2, data.Upgrade2);
    ApplyValue(1310, BuildingBrushDlg->CString_Upgrade3, data.Upgrade3);
    ApplyValue(1311, BuildingBrushDlg->CString_AIRepairs, data.AIRepairable);
    ApplyValue(1312, BuildingBrushDlg->CString_ShowName, data.Nominal);
    ApplyValue(1313, BuildingBrushDlg->CString_Tag, data.Tag);
}

void CViewObjectsExt::ApplyPropertyBrush_Infantry(CInfantryData& data)
{
    if (!InfantryBrushDlg)
        return;

    auto ApplyValue = [&](int nCheckBoxIdx, ppmfc::CString& src, ppmfc::CString& dst)
    {
        if (InfantryBrushBools[nCheckBoxIdx - 1300])
        {
            if (!src.IsEmpty())
                dst = src;
        }
    };

    ApplyValue(1300, InfantryBrushDlg->CString_House, data.House);
    ApplyValue(1301, InfantryBrushDlg->CString_HealthPoint, data.Health);
    ApplyValue(1302, InfantryBrushDlg->CString_State, data.Status);
    ApplyValue(1303, InfantryBrushDlg->CString_Direction, data.Facing);
    ApplyValue(1304, InfantryBrushDlg->CString_VerteranStatus, data.VeterancyPercentage);
    ApplyValue(1305, InfantryBrushDlg->CString_Group, data.Group);
    ApplyValue(1306, InfantryBrushDlg->CString_OnBridge, data.IsAboveGround);
    ApplyValue(1307, InfantryBrushDlg->CString_AutoCreateNoRecruitable, data.AutoNORecruitType);
    ApplyValue(1308, InfantryBrushDlg->CString_AutoCreateYesRecruitable, data.AutoYESRecruitType);
    ApplyValue(1309, InfantryBrushDlg->CString_Tag, data.Tag);
}

void CViewObjectsExt::ApplyPropertyBrush_Aircraft(CAircraftData& data)
{
    if (!AircraftBrushDlg)
        return;

    auto ApplyValue = [&](int nCheckBoxIdx, ppmfc::CString& src, ppmfc::CString& dst)
    {
        if (AircraftBrushBools[nCheckBoxIdx - 1300])
        {
            if (!src.IsEmpty())
                dst = src;
        }
    };

    ApplyValue(1300, AircraftBrushDlg->CString_House, data.House);
    ApplyValue(1301, AircraftBrushDlg->CString_HealthPoint, data.Health);
    ApplyValue(1302, AircraftBrushDlg->CString_Direction, data.Facing);
    ApplyValue(1303, AircraftBrushDlg->CString_Status, data.Status);
    ApplyValue(1304, AircraftBrushDlg->CString_VeteranLevel, data.VeterancyPercentage);
    ApplyValue(1305, AircraftBrushDlg->CString_Group, data.Group);
    ApplyValue(1306, AircraftBrushDlg->CString_AutoCreateNoRecruitable, data.AutoNORecruitType);
    ApplyValue(1307, AircraftBrushDlg->CString_AutoCreateYesRecruitable, data.AutoYESRecruitType);
    ApplyValue(1308, AircraftBrushDlg->CString_Tag, data.Tag);
}

void CViewObjectsExt::ApplyPropertyBrush_Vehicle(CUnitData& data)
{
    if (!VehicleBrushDlg)
        return;

    auto ApplyValue = [&](int nCheckBoxIdx, ppmfc::CString& src, ppmfc::CString& dst)
    {
        if (VehicleBrushBools[nCheckBoxIdx - 1300])
        {
            if (!src.IsEmpty())
                dst = src;
        }
    };

    ApplyValue(1300, VehicleBrushDlg->CString_House, data.House);
    ApplyValue(1301, VehicleBrushDlg->CString_HealthPoint, data.Health);
    ApplyValue(1302, VehicleBrushDlg->CString_State, data.Status);
    ApplyValue(1303, VehicleBrushDlg->CString_Direction, data.Facing);
    ApplyValue(1304, VehicleBrushDlg->CString_VeteranLevel, data.VeterancyPercentage);
    ApplyValue(1305, VehicleBrushDlg->CString_Group, data.Group);
    ApplyValue(1306, VehicleBrushDlg->CString_OnBridge, data.IsAboveGround);
    ApplyValue(1307, VehicleBrushDlg->CString_FollowerID, data.FollowsIndex);
    ApplyValue(1308, VehicleBrushDlg->CString_AutoCreateNoRecruitable, data.AutoNORecruitType);
    ApplyValue(1309, VehicleBrushDlg->CString_AutoCreateYesRecruitable, data.AutoYESRecruitType);
    ApplyValue(1310, VehicleBrushDlg->CString_Tag, data.Tag);
}

bool CViewObjectsExt::IsIgnored(const char* pItem)
{
    return IgnoreSet.find(pItem) != IgnoreSet.end();
}

int CViewObjectsExt::GuessType(const char* pRegName)
{
    if (ExtSets[Set_Building].find(pRegName) != ExtSets[Set_Building].end())
        return Set_Building;
    if (ExtSets[Set_Infantry].find(pRegName) != ExtSets[Set_Infantry].end())
        return Set_Infantry;
    if (ExtSets[Set_Vehicle].find(pRegName) != ExtSets[Set_Vehicle].end())
        return Set_Vehicle;
    if (ExtSets[Set_Aircraft].find(pRegName) != ExtSets[Set_Aircraft].end())
        return Set_Aircraft;
    return -1;
}

int CViewObjectsExt::GuessSide(const char* pRegName, int nType)
{
    auto& knownIterator = KnownItem.find(pRegName);
    if (knownIterator != KnownItem.end())
        return knownIterator->second;

    int result = -1;
    switch (nType)
    {
    case -1:
    default:
        break;
    case Set_Building:
        result = GuessBuildingSide(pRegName);
        break;
    case Set_Infantry:
        result = GuessGenericSide(pRegName, Set_Infantry);
        break;
    case Set_Vehicle:
        result = GuessGenericSide(pRegName, Set_Vehicle);
        break;
    case Set_Aircraft:
        result = GuessGenericSide(pRegName, Set_Aircraft);
        break;
    }
    KnownItem[pRegName] = result;
    return result;
}

int CViewObjectsExt::GuessBuildingSide(const char* pRegName)
{
    auto& rules = CINI::Rules();

    int planning;
    planning = rules.GetInteger(pRegName, "AIBasePlanningSide", -1);
    if (planning >= rules.GetKeyCount("Sides"))
        return -1;
    if (planning >= 0)
        return planning;
    auto& cons = STDHelpers::SplitString(rules.GetString("AI", "BuildConst"));
    int i;
    for (i = 0; i < cons.size(); ++i)
    {
        if (cons[i] == pRegName)
            return i;
    }
    if (i >= rules.GetKeyCount("Sides"))
        return -1;
    return GuessGenericSide(pRegName, Set_Building);
}

int CViewObjectsExt::GuessGenericSide(const char* pRegName, int nType)
{
    const auto& set = ExtSets[nType];

    if (set.find(pRegName) == set.end())
        return -1;

    switch (ExtConfigs::BrowserRedraw_GuessMode)
    {
    default:
    case 0:
    {
        for (auto& prep : STDHelpers::SplitString(Variables::Rules.GetString(pRegName, "Prerequisite")))
        {
            int guess = -1;
            for (auto& subprep : STDHelpers::SplitString(Variables::Rules.GetString("GenericPrerequisites", prep)))
            {
                if (subprep == pRegName) // Avoid build myself crash
                    return -1;
                guess = GuessSide(subprep, GuessType(subprep));
                if (guess != -1)
                    return guess;
            }
            if (prep == pRegName) // Avoid build myself crash
                return -1;
            guess = GuessSide(prep, GuessType(prep));
            if (guess != -1)
                return guess;
        }
        return -1;
    }
    case 1:
    {
        auto& owners = STDHelpers::SplitString(Variables::Rules.GetString(pRegName, "Owner"));
        if (owners.size() <= 0)
            return -1;
        auto& itr = Owners.find(owners[0]);
        if (itr == Owners.end())
            return -1;
        return itr->second;
    }
    }
}

// CViewObjectsExt::OnSelectChanged
void CViewObjectsExt::OnExeTerminate()
{
    IgnoreSet.clear();
    ForceName.clear();
    for (auto& set : ExtSets)
        set.clear();
    KnownItem.clear();
    Owners.clear();
}

bool CViewObjectsExt::UpdateEngine(int nData)
{
    do
    {
        int nMorphable = nData - 67;
        if (nMorphable >= 0 && nMorphable < TheaterInfo::CurrentInfo.size())
        {
            int i;
            for (i = 0; i < *CTileTypeClass::InstanceCount; ++i)
                if ((*CTileTypeClass::Instance)[i].TileSet == TheaterInfo::CurrentInfo[nMorphable].Morphable)
                {
                    CIsoView::CurrentCommand->Param = 0;
                    CIsoView::CurrentCommand->Height = 0;
                    CIsoView::CurrentCommand->Type = i;
                    CIsoView::CurrentCommand->Command = FACurrentCommand::TileDraw;
                    CBrushSize::UpdateBrushSize(i);
                    return true;
                }
        }
    } while (false);
    

    int nCode = nData / 10000;
    nData %= 10000;

    if (nCode == 9) // PropertyBrush
    {
        if (nData == Set_Building)
        {
            CViewObjectsExt::InitPropertyDlgFromProperty = true;

            if (this->DoPropertyBrush_Building())
            {
                CIsoView::CurrentCommand->Command = 0x17; // PropertyBrush
                CIsoView::CurrentCommand->Type = Set_Building;
            }
            else
                CIsoView::CurrentCommand->Command = FACurrentCommand::Nothing;

            CViewObjectsExt::InitPropertyDlgFromProperty = false;

            return true;
        }
        else if (nData == Set_Infantry)
        {
            CViewObjectsExt::InitPropertyDlgFromProperty = true;

            if (this->DoPropertyBrush_Infantry())
            {
                CIsoView::CurrentCommand->Command = 0x17;
                CIsoView::CurrentCommand->Type = Set_Infantry;
            }
            else
                CIsoView::CurrentCommand->Command = FACurrentCommand::Nothing;

            CViewObjectsExt::InitPropertyDlgFromProperty = false;

            return true;
        }
        else if (nData == Set_Vehicle)
        {
            CViewObjectsExt::InitPropertyDlgFromProperty = true;

            if (this->DoPropertyBrush_Vehicle())
            {
                CIsoView::CurrentCommand->Command = 0x17;
                CIsoView::CurrentCommand->Type = Set_Vehicle;
            }
            else
                CIsoView::CurrentCommand->Command = FACurrentCommand::Nothing;

            CViewObjectsExt::InitPropertyDlgFromProperty = false;

            return true;
        }
        else if (nData == Set_Aircraft)
        {
            CViewObjectsExt::InitPropertyDlgFromProperty = true;

            if (this->DoPropertyBrush_Aircraft())
            {
                CIsoView::CurrentCommand->Command = 0x17;
                CIsoView::CurrentCommand->Type = Set_Aircraft;
            }
            else
                CIsoView::CurrentCommand->Command = FACurrentCommand::Nothing;

            CViewObjectsExt::InitPropertyDlgFromProperty = false;

            return true;
        }
    }

    return false;
}