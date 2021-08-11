#include "Body.h"

#include <GlobalVars.h>
#include <CINI.h>
#include <CMapData.h>
#include <CMixFile.h>
#include <CShpFile.h>
#include <Drawing.h>
#include <CPalette.h>

#include "../../Miscs/DrawStuff.h"
#include "../../Miscs/Palettes.h"
#include "../../FA2sp.h"

std::vector<CLoadingExt::SHPUnionData> CLoadingExt::UnionSHP_Data[2];
std::map<ppmfc::CString, CLoadingExt::ObjectType> CLoadingExt::ObjectTypes;
unsigned char CLoadingExt::VXL_Data[0x10000] = {0};

ppmfc::CString CLoadingExt::GetImageName(ppmfc::CString ID, int nFacing)
{
	ppmfc::CString ImageID;
	ppmfc::CString DictName;
	CLoadingExt* pLoading = (CLoadingExt*)GlobalVars::Dialogs::CLoading();
	switch (pLoading->GetItemType(ID))
	{
	case ObjectType::Infantry:
	{
		ImageID = pLoading->GetInfantryFileID(ID);
		DictName.Format("%s%d", ImageID, nFacing);
		return DictName;
	}
	case ObjectType::Aircraft:
	case ObjectType::Vehicle:
		ImageID = pLoading->GetVehicleOrAircraftFileID(ID);
		DictName.Format("%s%d", ImageID, nFacing);
		return DictName;
	case ObjectType::Building:
	 	ImageID = pLoading->GetBuildingFileID(ID);
	 	DictName.Format("%s%d", ImageID, nFacing);
	 	return DictName;
	default: // NEVER GET TO HERE PLS
		return "NMSL";
	}

}

CLoadingExt::ObjectType CLoadingExt::GetItemType(ppmfc::CString ID)
{
	if (ObjectTypes.size() == 0)
	{
		auto load = [](ppmfc::CString type, ObjectType e)
		{
			auto section = Variables::Rules.GetSection(type);
			for (auto& pair : section)
				ObjectTypes[pair.second] = e;
		};

		load("InfantryTypes", ObjectType::Infantry);
		load("VehicleTypes", ObjectType::Vehicle);
		load("AircraftTypes", ObjectType::Aircraft);
		load("BuildingTypes", ObjectType::Building);
		load("SmudgeTypes", ObjectType::Smudge);
		load("TerrainTypes", ObjectType::Terrain);
	}

	auto itr = ObjectTypes.find(ID);
	if (itr != ObjectTypes.end())
		return itr->second;
	return ObjectType::Unknown;
}

void CLoadingExt::LoadObjects(ppmfc::CString ID)
{
    Logger::Debug("CLoadingExt::LoadObjects loading: %s\n", ID);

	// GlobalVars::CMapData->UpdateCurrentDocument();
	auto eItemType = GetItemType(ID);
	switch (eItemType)
	{
	case CLoadingExt::ObjectType::Infantry:
		LoadInfantry(ID);
		break;
	case CLoadingExt::ObjectType::Terrain:
	case CLoadingExt::ObjectType::Smudge:
		LoadTerrainOrSmudge(ID);
		break;
	case CLoadingExt::ObjectType::Vehicle:
	case CLoadingExt::ObjectType::Aircraft:
		LoadVehicleOrAircraft(ID);
		break;
	case CLoadingExt::ObjectType::Building:
		LoadBuilding(ID);
		break;
	case CLoadingExt::ObjectType::Unknown:
	default:
		break;
	}
}

ppmfc::CString CLoadingExt::GetTerrainOrSmudgeFileID(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);
	if (auto ppImage = Variables::Rules.TryGetString(ID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = ID;

	ppmfc::CString ImageID = GlobalVars::INIFiles::Art->GetString(ArtID, "Image", ArtID);

	return ImageID;
}

ppmfc::CString CLoadingExt::GetBuildingFileID(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);
	ppmfc::CString ImageID = GlobalVars::INIFiles::Art->GetString(ArtID, "Image", ArtID);

	ppmfc::CString backupID = ImageID;
	SetTheaterLetter(ImageID);

	ppmfc::CString validator = ImageID + ".SHP";
	int nMix = this->SearchFile(validator);
	if (!CMixFile::HasFile(validator, nMix))
	{
		SetGenericTheaterLetter(ImageID);
		validator = ImageID + ".SHP";
		nMix = this->SearchFile(validator);
		if (!CMixFile::HasFile(validator, nMix))
			ImageID = backupID;
	}
	return ImageID;
}

ppmfc::CString CLoadingExt::GetInfantryFileID(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);

	ppmfc::CString ImageID = GlobalVars::INIFiles::Art->GetString(ArtID, "Image", ArtID);

	if (Variables::Rules.GetBool(ID, "AlternateTheaterArt"))
		ImageID += this->TheaterIdentifier;
	else if (Variables::Rules.GetBool(ID, "AlternateArcticArt"))
		if (this->TheaterIdentifier == 'A')
			ImageID += 'A';
	if (!GlobalVars::INIFiles::Art->SectionExists(ImageID))
		ImageID = ArtID;

	return ImageID;
}

ppmfc::CString CLoadingExt::GetArtID(ppmfc::CString ID)
{
	ppmfc::CString ArtID;
	if (auto ppImage = Variables::Rules.TryGetString(ID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = ID;

	return ArtID;
}

ppmfc::CString CLoadingExt::GetVehicleOrAircraftFileID(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);

	ppmfc::CString ImageID = GlobalVars::INIFiles::Art->GetString(ArtID, "Image", ArtID);

	return ImageID;
}

void CLoadingExt::LoadBuilding(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);
	ppmfc::CString ImageID = GetBuildingFileID(ID);

	auto loadBuildingFrameShape = [&](ppmfc::CString name, int nFrame = 0, int deltaX = 0, int deltaY = 0) -> bool
	{
		ppmfc::CString file = name + ".SHP";
		int nMix = SearchFile(file);
		if (!CMixFile::HasFile(file, nMix))
			return false;

		ShapeHeader header;
		unsigned char* pBuffer;
		CMixFile::LoadSHP(file, nMix);
		CShpFile::GetSHPHeader(&header);
		CShpFile::LoadFrame(nFrame, 1, &pBuffer);

		UnionSHP_Add(pBuffer, header.Width, header.Height, deltaX, deltaY);

		return true;
	};

	auto loadSingleFrameShape = [&](ppmfc::CString name,int nFrame = 0, int deltaX = 0 ,int deltaY = 0) -> bool
	{
		ppmfc::CString file = name + ".SHP";
		SetTheaterLetter(file);
		int nMix = SearchFile(file);
		if (!CMixFile::HasFile(file, nMix))
		{
			SetGenericTheaterLetter(file);
			nMix = SearchFile(file);
			if (!CMixFile::HasFile(file, nMix))
			{
				file = name + ".SHP";
				int nMix = SearchFile(file);
				if (!CMixFile::HasFile(file, nMix))
					return false;
			}
		}
		
		ShapeHeader header;
		unsigned char* pBuffer;
		CMixFile::LoadSHP(file, nMix);
		CShpFile::GetSHPHeader(&header);
		CShpFile::LoadFrame(nFrame, 1, &pBuffer);
		
		UnionSHP_Add(pBuffer, header.Width, header.Height, deltaX, deltaY);
			
		return true;
	};

	if (auto ppPowerUpBld = Variables::Rules.TryGetString(ID, "PowersUpBuilding")) // Early load
	{
		ppmfc::CString SrcBldName = GetBuildingFileID(*ppPowerUpBld) + "0";
		if (!ImageDataMapHelper::IsImageLoaded(SrcBldName))
			LoadBuilding(*ppPowerUpBld);
	}

	int nBldStartFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "LoopStart", 0);
	if (loadBuildingFrameShape(ImageID, nBldStartFrame))
	{
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "IdleAnim"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreIdleAnim", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "ActiveAnim"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreActiveAnim1", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "ActiveAnimTwo"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreActiveAnim2", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "ActiveAnimThree"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreActiveAnim3", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "ActiveAnimFour"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreActiveAnim4", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "SuperAnim"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreSuperAnim1", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "SuperAnimTwo"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreSuperAnim2", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "SuperAnimThree"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreSuperAnim3", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "SuperAnimFour"))
		{
			if (!GlobalVars::INIFiles::FAData->GetBool("IgnoreSuperAnim4", ID))
			{
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(*ppStr, "LoopStart");
				loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr), nStartFrame);
			}
		}
		if (auto ppStr = GlobalVars::INIFiles::Art->TryGetString(ArtID, "BibShape"))
			loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(*ppStr, "Image", *ppStr));

		ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ArtID, "Palette", "unit");
		if (GlobalVars::INIFiles::Art->GetBool(ArtID, "TerrainPalette"))
			PaletteName = "iso";
		GetFullPaletteName(PaletteName);

		ppmfc::CString DictName;

		unsigned char* pBuffer;
		int width, height;
		UnionSHP_GetAndClear(pBuffer, &width, &height);

		if (Variables::Rules.GetBool(ID, "Turret")) // Has turret
		{
			if (Variables::Rules.GetBool(ID, "TurretAnimIsVoxel"))
			{
				int turzadjust = Variables::Rules.GetInteger(ID, "TurretAnimZAdjust");

				ppmfc::CString TurName = Variables::Rules.GetString(ID, "TurretAnim", ID + "tur");
				ppmfc::CString BarlName = ID + "barl";

				
				if (!DrawStuff::is_vpl_loaded())
					DrawStuff::load_vpl("voxels.vpl");

				unsigned char* pTurImages[8]{ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
				unsigned char* pBarlImages[8]{ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
				int turrect[8][4] = { 0 }, barlrect[8][4] = {0};

				ppmfc::CString VXLName = BarlName + ".vxl";
				ppmfc::CString HVAName = BarlName + ".hva";
				if (DrawStuff::load_vxl(VXLName))
					if (DrawStuff::load_hva(HVAName))
						for (int i = 0; i < 8; ++i)
						{
							// (13 - i) % 8 for facing fix
							bool result = DrawStuff::get_to_image((13 - i) % 8, pBarlImages[i],
								barlrect[i][0], barlrect[i][1], barlrect[i][2], barlrect[i][3], turzadjust);
							if (!result)
								break;
						}

				VXLName = TurName + ".vxl";
				HVAName = TurName + ".hva";
				if (DrawStuff::load_vxl(VXLName))
					if (DrawStuff::load_hva(HVAName))
						for (int i = 0; i < 8; ++i)
						{
							// (13 - i) % 8 for facing fix
							bool result = DrawStuff::get_to_image((13 - i) % 8, pTurImages[i],
								turrect[i][0], turrect[i][1], turrect[i][2], turrect[i][3], pBarlImages[i] ? 0 : turzadjust);
							if (!result)
								break;
						}

				for (int i = 0; i < 8; ++i)
				{
					auto pTempBuf = GameCreateArray<unsigned char>(width * height);
					memcpy_s(pTempBuf, width* height, pBuffer, width* height);
					UnionSHP_Add(pTempBuf, width, height);

					int deltaX = Variables::Rules.GetInteger(ID, "TurretAnimX", 0);
					int deltaY = Variables::Rules.GetInteger(ID, "TurretAnimY", 0);

					if (pTurImages[i])
					{
						ppmfc::CString pKey;

						pKey.Format("%sX%d", ID, (15 - i) % 8);
						int turdeltaX = GlobalVars::INIFiles::FAData->GetInteger("BuildingVoxelTurretsRA2", pKey);
						pKey.Format("%sY%d", ID, (15 - i) % 8);
						int turdeltaY = GlobalVars::INIFiles::FAData->GetInteger("BuildingVoxelTurretsRA2", pKey);

						VXL_Add(pTurImages[i], turrect[i][2] + turdeltaX, turrect[i][3] + turdeltaY, turrect[i][0], turrect[i][1]);
						GameDeleteArray(pTurImages[i], turrect[i][0] * turrect[i][1]);

						if (pBarlImages[i])
						{
							pKey.Format("%sX%d", ID, (15 - i) % 8);
							int barldeltaX = GlobalVars::INIFiles::FAData->GetInteger("BuildingVoxelBarrelsRA2", pKey);
							pKey.Format("%sY%d", ID, (15 - i) % 8);
							int barldeltaY = GlobalVars::INIFiles::FAData->GetInteger("BuildingVoxelBarrelsRA2", pKey);

							VXL_Add(pBarlImages[i], barlrect[i][2]+ barldeltaX, barlrect[i][3]+ barldeltaY, barlrect[i][0], barlrect[i][1]);
							GameDeleteArray(pBarlImages[i], barlrect[i][0] * barlrect[i][1]);
						}
					}

					int nW = 0x100, nH = 0x100;
					VXL_GetAndClear(pTurImages[i], &nW, &nH);

					UnionSHP_Add(pTurImages[i], 0x100, 0x100, deltaX, deltaY);

					unsigned char* pImage;
					int width1, height1;

					UnionSHP_GetAndClear(pImage, &width1, &height1);
					DictName.Format("%s%d", ImageID, i);
					SetImageData(pImage, DictName, width1, height1, Palettes::LoadPalette(PaletteName));
				}

				GameDeleteArray(pBuffer, width * height);
			}
			else //SHP anim
			{
				ppmfc::CString TurName = Variables::Rules.GetString(ID, "TurretAnim", ID + "tur");
				int nStartFrame = GlobalVars::INIFiles::Art->GetInteger(TurName, "LoopStart");
				for (int i = 0; i < 8; ++i)
				{
					auto pTempBuf = GameCreateArray<unsigned char>(width * height);
					memcpy_s(pTempBuf, width * height, pBuffer, width * height);
					UnionSHP_Add(pTempBuf, width, height);

					int deltaX = Variables::Rules.GetInteger(ID, "TurretAnimX", 0);
					int deltaY = Variables::Rules.GetInteger(ID, "TurretAnimY", 0);
					loadSingleFrameShape(GlobalVars::INIFiles::Art->GetString(TurName, "Image", TurName),
						nStartFrame + i * 4, deltaX, deltaY);

					unsigned char* pImage;
					int width1, height1;
					UnionSHP_GetAndClear(pImage, &width1, &height1);

					DictName.Format("%s%d", ImageID, i);
					SetImageData(pImage, DictName, width1, height1, Palettes::LoadPalette(PaletteName));
				}
				GameDelete(pBuffer);
			}
		}
		else // No turret
		{
			DictName.Format("%s%d", ImageID, 0);
			SetImageData(pBuffer, DictName, width, height, Palettes::LoadPalette(PaletteName));
		}
	}
}

void CLoadingExt::LoadInfantry(ppmfc::CString ID)
{	
	ppmfc::CString ArtID = GetArtID(ID);
	ppmfc::CString ImageID = GetInfantryFileID(ID);

	ppmfc::CString sequenceName = GlobalVars::INIFiles::Art->GetString(ImageID, "Sequence");
	ppmfc::CString frames = GlobalVars::INIFiles::Art->GetString(sequenceName, "Guard", "0,1,1");
	int framesToRead[8];
	int frameStart, frameStep;
	sscanf_s(frames, "%d,%d,%d", &frameStart, &framesToRead[0], &frameStep);
	for (int i = 0; i < 8; ++i)
		framesToRead[i] = frameStart + i * frameStep;
	
	ppmfc::CString FileName = ImageID + ".shp";
	int nMix = this->SearchFile(FileName);
	if (CMixFile::HasFile(FileName, nMix))
	{
		ShapeHeader header;
		unsigned char* FramesBuffers;
		CMixFile::LoadSHP(FileName, nMix);
		CShpFile::GetSHPHeader(&header);
		for (int i = 0; i < 8; ++i)
		{
			CShpFile::LoadFrame(framesToRead[i], 1, &FramesBuffers);
			ppmfc::CString DictName;
			DictName.Format("%s%d", ImageID, i);
			ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ArtID, "Palette", "unit");
			GetFullPaletteName(PaletteName);
			SetImageData(FramesBuffers, DictName, header.Width, header.Height, Palettes::LoadPalette(PaletteName));
		}
	}
}

void CLoadingExt::LoadTerrainOrSmudge(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);
	ppmfc::CString ImageID = GetTerrainOrSmudgeFileID(ID);
	ppmfc::CString FileName = ImageID + this->GetFileExtension();
	int nMix = this->SearchFile(FileName);
	if (CMixFile::HasFile(FileName, nMix))
	{
		ShapeHeader header;
		unsigned char* FramesBuffers[1];
		CMixFile::LoadSHP(FileName, nMix);
		CShpFile::GetSHPHeader(&header);
		CShpFile::LoadFrame(0, 1, &FramesBuffers[0]);
		ppmfc::CString DictName;
		DictName.Format("%s%d", ImageID, 0);
		ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ArtID, "Palette", "iso");
		GetFullPaletteName(PaletteName);
		SetImageData(FramesBuffers[0], DictName, header.Width, header.Height, Palettes::LoadPalette(PaletteName));
	}
}

void CLoadingExt::LoadVehicleOrAircraft(ppmfc::CString ID)
{
	ppmfc::CString ArtID = GetArtID(ID);
	ppmfc::CString ImageID = GetVehicleOrAircraftFileID(ID);
	bool bHasTurret = Variables::Rules.GetBool(ID, "Turret");

	if (GlobalVars::INIFiles::Art->GetBool(ArtID, "Voxel")) // As VXL
	{
		ppmfc::CString FileName = ImageID + ".vxl";
		ppmfc::CString HVAName = ImageID + ".hva";

		if (!DrawStuff::is_vpl_loaded())
			DrawStuff::load_vpl("voxels.vpl");

		ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ArtID, "Palette", "unit");
		GetFullPaletteName(PaletteName);

		unsigned char* pImage[8]{ nullptr,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };
		unsigned char* pTurretImage[8]{ nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };
		unsigned char* pBarrelImage[8]{ nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr ,nullptr };
		int rect[8][4], turretrect[8][4], barrelrect[8][4];
		if (DrawStuff::load_vxl(FileName))
			if (DrawStuff::load_hva(HVAName))
				for (int i = 0; i < 8; ++i)
				{
					// (i+6) % 8 to fix the facing
					bool result = DrawStuff::get_to_image((i + 6) % 8, pImage[i], 
						rect[i][0], rect[i][1], rect[i][2], rect[i][3]);
					if (!result)
						return;
				}

		if (bHasTurret)
		{
			int F, L, H;
			int s_count = sscanf_s(GlobalVars::INIFiles::Art->GetString(ArtID, "TurretOffset", "0,0,0"), "%d,%d,%d", &F, &L, &H);
			if (s_count == 0) F = L = H = 0;
			else if (s_count == 1) L = H = 0;
			else if (s_count == 2) H = 0;

			ppmfc::CString turFileName = ImageID + "tur.vxl";
			ppmfc::CString turHVAName = ImageID + "tur.hva";
			if (DrawStuff::load_vxl(turFileName))
				if (DrawStuff::load_hva(turHVAName))
					for (int i = 0; i < 8; ++i)
					{
						// (i+6) % 8 to fix the facing
						bool result = DrawStuff::get_to_image((i + 6) % 8, pTurretImage[i],
							turretrect[i][0], turretrect[i][1], turretrect[i][2], turretrect[i][3], F, L, H);

						if (!result)
							break;
					}

			ppmfc::CString barlFileName = ImageID + "barl.vxl";
			ppmfc::CString barlHVAName = ImageID + "barl.hva";
			if (DrawStuff::load_vxl(barlFileName))
				if (DrawStuff::load_hva(barlHVAName))
					for (int i = 0; i < 8; ++i)
					{
						// (i+6) % 8 to fix the facing
						bool result = DrawStuff::get_to_image((i + 6) % 8, pBarrelImage[i],
							barrelrect[i][0], barrelrect[i][1], barrelrect[i][2], barrelrect[i][3], F, L, H);

						if (!result)
							break;
					}

			for (int i = 0; i < 8; ++i)
			{
				ppmfc::CString DictName;
				DictName.Format("%s%d", ImageID, i);

				unsigned char* outBuffer;
				int outW = 0x100, outH = 0x100;

				if (pImage[i])
				{
					VXL_Add(pImage[i], rect[i][2], rect[i][3], rect[i][0], rect[i][1]);
					GameDeleteArray(pImage[i], rect[i][0] * rect[i][1]);
				}
				ppmfc::CString pKey;
				if (pTurretImage[i])
				{
					pKey.Format("%sX%d", ID, i);
					int turdeltaX = GlobalVars::INIFiles::FAData->GetInteger("VehicleVoxelTurretsRA2", pKey);
					pKey.Format("%sY%d", ID, i);
					int turdeltaY = GlobalVars::INIFiles::FAData->GetInteger("VehicleVoxelTurretsRA2", pKey);
					VXL_Add(pTurretImage[i], turretrect[i][2] + turdeltaX, turretrect[i][3] + turdeltaY, turretrect[i][0], turretrect[i][1]);
					GameDeleteArray(pTurretImage[i], turretrect[i][0] * turretrect[i][1]);

					if (pBarrelImage[i])
					{
						pKey.Format("%sX%d", ID, i);
						int barldeltaX = GlobalVars::INIFiles::FAData->GetInteger("VehicleVoxelBarrelsRA2", pKey);
						pKey.Format("%sY%d", ID, i);
						int barldeltaY = GlobalVars::INIFiles::FAData->GetInteger("VehicleVoxelBarrelsRA2", pKey);

						VXL_Add(pBarrelImage[i], barrelrect[i][2] + barldeltaX, barrelrect[i][3] + barldeltaY, barrelrect[i][0], barrelrect[i][1]);
						GameDeleteArray(pBarrelImage[i], barrelrect[i][0] * barrelrect[i][1]);
					}
				}

				VXL_GetAndClear(outBuffer, &outW, &outH);

				SetImageData(outBuffer, DictName, outW, outH, Palettes::LoadPalette(PaletteName));
			}
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				ppmfc::CString DictName;
				DictName.Format("%s%d", ImageID, i);

				unsigned char* outBuffer;
				int outW = 0x100, outH = 0x100;

				VXL_Add(pImage[i], rect[i][2], rect[i][3], rect[i][0], rect[i][1]);
				VXL_GetAndClear(outBuffer, &outW, &outH);

				SetImageData(outBuffer, DictName, outW, outH, Palettes::LoadPalette(PaletteName));
			}
		}


	}
	else // As SHP
	{
		int framesToRead[8];
		if (GlobalVars::INIFiles::Art->KeyExists(ArtID, "StandingFrames"))
		{
			int nStartStandFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "StartStandFrame", 0);
			int nStandingFrames = GlobalVars::INIFiles::Art->GetInteger(ArtID, "StandingFrames", 1);
			for (int i = 0; i < 8; ++i)
				framesToRead[i] = nStartStandFrame + i * nStandingFrames;
		}
		else
		{
			int nStartWalkFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "StartWalkFrame", 0);
			int nWalkFrames = GlobalVars::INIFiles::Art->GetInteger(ArtID, "WalkFrames", 1);
			for (int i = 0; i < 8; ++i) {
				framesToRead[i] = nStartWalkFrame + i * nWalkFrames;
			}
		}
		// fix from cmcc
		int temp = framesToRead[0];
		for (int i = 0; i < 7; i++)
			framesToRead[i] = framesToRead[i + 1];
		framesToRead[7] = temp;

		ppmfc::CString FileName = ImageID + ".shp";
		int nMix = this->SearchFile(FileName);
		if (CMixFile::HasFile(FileName, nMix))
		{
			ShapeHeader header;
			unsigned char* FramesBuffers[2];
			CMixFile::LoadSHP(FileName, nMix);
			CShpFile::GetSHPHeader(&header);
			for (int i = 0; i < 8; ++i)
			{
				CShpFile::LoadFrame(framesToRead[i], 1, &FramesBuffers[0]);
				ppmfc::CString DictName;
				DictName.Format("%s%d", ImageID, i);
				ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ArtID, "Palette", "unit");
				GetFullPaletteName(PaletteName);

				if (bHasTurret)
				{
					int nStartWalkFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "StartWalkFrame", 0);
					int nWalkFrames = GlobalVars::INIFiles::Art->GetInteger(ArtID, "WalkFrames", 1);
					int turretFramesToRead[8];
					
					// fix from cmcc
					turretFramesToRead[i] = nStartWalkFrame + 8 * nWalkFrames + 4 * ((i + 1) % 8);

					CShpFile::LoadFrame(turretFramesToRead[i], 1, &FramesBuffers[1]);
					UnionSHP_Add(FramesBuffers[0], header.Width, header.Height);
					UnionSHP_Add(FramesBuffers[1], header.Width, header.Height);
					unsigned char* outBuffer;
					int outW, outH;
					UnionSHP_GetAndClear(outBuffer, &outW, &outH);
					
					SetImageData(outBuffer, DictName, outW, outH, Palettes::LoadPalette(PaletteName));
				}
				else
					SetImageData(FramesBuffers[0], DictName, header.Width, header.Height, Palettes::LoadPalette(PaletteName));
			}
		}
	}
}

void CLoadingExt::SetImageData(unsigned char* pBuffer, ppmfc::CString NameInDict, int FullWidth, int FullHeight, Palette* pPal)
{
	auto pData = ImageDataMapHelper::GetImageDataFromMap(NameInDict);
	SetImageData(pBuffer, pData, FullWidth, FullHeight, pPal);
}

void CLoadingExt::SetImageData(unsigned char* pBuffer, ImageDataClass* pData, int FullWidth, int FullHeight, Palette* pPal)
{
	if (pData->pImageBuffer)
		GameDeleteArray(pData->pImageBuffer, pData->FullWidth * pData->FullHeight);
	if (pData->pPixelValidRanges)
		GameDeleteArray(pData->pPixelValidRanges, pData->FullHeight);

	pData->pImageBuffer = pBuffer;
	pData->FullHeight = FullHeight;
	pData->FullWidth = FullWidth;
	SetValidBuffer(pData, FullWidth, FullHeight);

	// Get available area
	int counter = 0;
	int validFirstX = FullWidth - 1;
	int validFirstY = FullHeight - 1;
	int validLastX = 0;
	int validLastY = 0;
	for (int j = 0; j < FullHeight; ++j)
	{
		for (int i = 0; i < FullWidth; ++i)
		{
			unsigned char ch = pBuffer[counter++];
			if (ch != 0)
			{
				if (i < validFirstX)
					validFirstX = i;
				if (j < validFirstY)
					validFirstY = j;
				if (i > validLastX)
					validLastX = i;
				if (j > validLastY)
					validLastY = j;
			}
		}
	}

	pData->ValidX = validFirstX;
	pData->ValidY = validFirstY;
	pData->ValidWidth = validLastX - validFirstX + 1;
	pData->ValidHeight = validLastY - validFirstY + 1;

	pData->Flag = ImageDataFlag::SHP;
	pData->IsOverlay = false;
	pData->pPalette = pPal ? pPal : Palette::PALETTE_UNIT;
}
// This function will shrink it to fit.
// Also will delete the origin buffer and create a new buffer.
void CLoadingExt::ShrinkSHP(unsigned char* pIn, int InWidth, int InHeight, unsigned char*& pOut, int* OutWidth, int* OutHeight)
{
	int counter = 0;
	int validFirstX = InWidth - 1;
	int validFirstY = InHeight - 1;
	int validLastX = 0;
	int validLastY = 0;
	for (int j = 0; j < InHeight; ++j)
	{
		for (int i = 0; i < InWidth; ++i)
		{
			unsigned char ch = pIn[counter++];
			if (ch != 0)
			{
				if (i < validFirstX)
					validFirstX = i;
				if (j < validFirstY)
					validFirstY = j;
				if (i > validLastX)
					validLastX = i;
				if (j > validLastY)
					validLastY = j;
			}
		}
	}

	counter = 0;
	*OutWidth = validLastX - validFirstX + 1;
	*OutHeight = validLastY - validFirstY + 1;
	pOut = GameCreateArray<unsigned char>(*OutWidth * *OutHeight);
	for (int j = 0; j < *OutHeight; ++j)
		memcpy_s(&pOut[j * *OutWidth], *OutWidth, &pIn[(j + validFirstY) * InWidth + validFirstX], *OutWidth);

	GameDeleteArray(pIn, InWidth * InHeight);
}

void CLoadingExt::UnionSHP_Add(unsigned char* pBuffer, int Width, int Height, int DeltaX, int DeltaY, bool UseTemp)
{
	UnionSHP_Data[UseTemp].push_back(SHPUnionData{ pBuffer,Width,Height,DeltaX,DeltaY });
}

void CLoadingExt::UnionSHP_GetAndClear(unsigned char*& pOutBuffer, int* OutWidth, int* OutHeight, bool UseTemp)
{
	// never calls it when UnionSHP_Data is empty

	if (UnionSHP_Data[UseTemp].size() == 1)
	{
		pOutBuffer = UnionSHP_Data[UseTemp][0].pBuffer;
		*OutWidth = UnionSHP_Data[UseTemp][0].Width;
		*OutHeight = UnionSHP_Data[UseTemp][0].Height;
		UnionSHP_Data[UseTemp].clear();
		return;
	}

	// For each shp, we make their center at the same point, this will give us proper result.
	int W = 0, H = 0;

	for (auto& data : UnionSHP_Data[UseTemp])
	{
		if (W < data.Width + 2 * abs(data.DeltaX)) W = data.Width + 2 * abs(data.DeltaX);
		if (H < data.Height + 2 * abs(data.DeltaY)) H = data.Height + 2 * abs(data.DeltaY);
	}

	// just make it work like unsigned char[W][H];
	pOutBuffer = GameCreateArray<unsigned char>(W * H);
	*OutWidth = W;
	*OutHeight = H;

	int ImageCenterX = W / 2;
	int ImageCenterY = H / 2;

	// Image[X][Y] <=> pOutBuffer[Y * W + X];
	for (auto& data : UnionSHP_Data[UseTemp])
	{
		int nStartX = ImageCenterX - data.Width / 2 + data.DeltaX;
		int nStartY = ImageCenterY - data.Height / 2 + data.DeltaY;

		for (int j = 0; j < data.Height; ++j)
			for (int i = 0; i < data.Width; ++i)
				if (auto nPalIdx = data.pBuffer[j * data.Width + i])
					pOutBuffer[(nStartY + j) * W + nStartX + i] = nPalIdx;

		GameDeleteArray(data.pBuffer, data.Width * data.Height);
	}

	UnionSHP_Data[UseTemp].clear();
}

void CLoadingExt::VXL_Add(unsigned char* pCache, int X, int Y, int Width, int Height)
{
	for (int j = 0; j < Height; ++j)
		for (int i = 0; i < Width; ++i)
			if (auto ch = pCache[j * Width + i])
				VXL_Data[(j + Y) * 0x100 + X + i] = ch;
}

void CLoadingExt::VXL_GetAndClear(unsigned char*& pBuffer, int* OutWidth, int* OutHeight)
{
	/* TODO : Save memory
	int validFirstX = 0x100 - 1;
	int validFirstY = 0x100 - 1;
	int validLastX = 0;
	int validLastY = 0;

	for (int j = 0; j < 0x100; ++j)
	{
		for (int i = 0; i < 0x100; ++i)
		{
			unsigned char ch = VXL_Data[j * 0x100 + i];
			if (ch != 0)
			{
				if (i < validFirstX)
					validFirstX = i;
				if (j < validFirstY)
					validFirstY = j;
				if (i > validLastX)
					validLastX = i;
				if (j > validLastY)
					validLastY = j;
			}
		}
	}
	*/
	pBuffer = GameCreateArray<unsigned char>(0x10000);
	memcpy_s(pBuffer, 0x10000, VXL_Data, 0x10000);
	memset(VXL_Data, 0, 0x10000);
}

void CLoadingExt::SetValidBuffer(ImageDataClass* pData, int Width, int Height)
{
	pData->pPixelValidRanges = GameCreateArray<ImageDataClass::ValidRangeData>(Height);
	for (int i = 0; i < Height; ++i)
	{
		int begin, end;
		this->GetSHPValidRange(pData->pImageBuffer, Width, i, &begin, &end);
		pData->pPixelValidRanges[i].First = begin;
		pData->pPixelValidRanges[i].Last = end;
	}
}

void CLoadingExt::GetFullPaletteName(ppmfc::CString& PaletteName)
{
	switch (this->TheaterIdentifier)
	{
	case 'A':
		PaletteName += "sno.pal";
		return;
	case 'U':
		PaletteName += "urb.pal";
		return;
	case 'N':
		PaletteName += "ubn.pal";
		return;
	case 'D':
		PaletteName += "des.pal";
		return;
	case 'L':
		PaletteName += "lun.pal";
		return;
	case 'T':
	default:
		PaletteName += "tem.pal";
		return;
	}
}

#include "../../Helpers/Bitmap.h"
void CLoadingExt::DumpFrameToFile(unsigned char* pBuffer, Palette* pPal, int Width, int Height, ppmfc::CString name)
{
	bitmap_image bmp;
	bmp.setwidth_height(Width, Height, true);
	
	int count = 0;
	for (int j = 0; j < bmp.height(); ++j)
	{
	    for (int i = 0; i < bmp.width(); ++i)
	    {
	        bmp.set_pixel(i, j, pPal->GetByteColor(pBuffer[count]));
	        ++count;
	    }
	}
	
	bmp.save_image((const char*)name);
}