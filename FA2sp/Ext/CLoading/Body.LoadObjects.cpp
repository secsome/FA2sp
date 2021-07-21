#include "Body.h"

#include <GlobalVars.h>
#include <CINI.h>
#include <CMixFile.h>
#include <CShpFile.h>
#include <Drawing.h>
#include <CPalette.h>

#include "../../Miscs/Palettes.h"
#include "../../FA2sp.h"

std::vector<CLoadingExt::SHPUnionData> CLoadingExt::UnionSHP_Data;
std::map<ppmfc::CString, CLoadingExt::ObjectType> CLoadingExt::ObjectTypes;

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
	default:
		ppmfc::CString buffer;
		buffer.Format("%s%d", buffer, nFacing);
		return buffer;
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
	ppmfc::CString ret = ID;
	if (GlobalVars::INIFiles::Art->GetBool(ID, "NewTheater"))
		ret.SetAt(1, this->TheaterIdentifier);
	return ret;
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
	
}

void CLoadingExt::LoadInfantry(ppmfc::CString ID)
{	
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
			ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ImageID, "Palette", "unit");
			GetFullPaletteName(PaletteName);
			SetImageData(FramesBuffers, DictName, header.Width, header.Height, Palettes::LoadPalette(PaletteName));
		}
	}
}

void CLoadingExt::LoadTerrainOrSmudge(ppmfc::CString ID)
{
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
		ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ImageID, "Palette", "iso");
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
	}
	else // As SHP
	{
		int framesToRead[8];
		int nStartStandFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "nStartStandFrame", 0);
		int nStandingFrames = GlobalVars::INIFiles::Art->GetInteger(ArtID, "nStandingFrames", 1);
		for (int i = 0; i < 8; ++i)
			framesToRead[i] = nStartStandFrame + i * nStandingFrames;

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
				ppmfc::CString PaletteName = GlobalVars::INIFiles::Art->GetString(ImageID, "Palette", "unit");
				GetFullPaletteName(PaletteName);

				if (bHasTurret)
				{
					int nStartWalkFrame = GlobalVars::INIFiles::Art->GetInteger(ArtID, "StartWalkFrame", 0);
					int nWalkFrames = GlobalVars::INIFiles::Art->GetInteger(ArtID, "WalkFrames", 1);
					int turretFramesToRead[8];
					turretFramesToRead[i] = nStartWalkFrame + 8 * nWalkFrames + 4 * i;
					CShpFile::LoadFrame(turretFramesToRead[i], 1, &FramesBuffers[1]);
					UnionSHP_Add(FramesBuffers[0], 0, 0, header.Width, header.Height);
					UnionSHP_Add(FramesBuffers[1], 0, 0, header.Width, header.Height);
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
	// unsigned char* pCompressedBuffer = nullptr;
	// int nWidth, nHeight;

	// ShrinkSHP(pBuffer, FullWidth, FullHeight, pCompressedBuffer, &nWidth, &nHeight);

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


	// SomeDataMapHelper::SetSomeData(NameInDict, true);
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

	GameDelete(pIn);
}

void CLoadingExt::UnionSHP_Add(unsigned char* pBuffer, int X, int Y, int Width, int Height)
{
	UnionSHP_Data.push_back(SHPUnionData{ pBuffer,X,Y,Width,Height });
}

void CLoadingExt::UnionSHP_GetAndClear(unsigned char*& pOutBuffer, int* OutWidth, int* OutHeight)
{
	// never calls it when UnionSHP_Data is empty

	// union rect
	int L = INT_MAX, T = INT_MAX, R = INT_MIN, B = INT_MIN;
	for (auto& data : UnionSHP_Data)
	{
		if (data.X < L) L = data.X;
		if (data.Y < T) T = data.Y;
		if (data.X + data.Width > R) R = data.X + data.Width;
		if (data.Y + data.Height > B)	B = data.Y + data.Height;
	}

	*OutWidth = R - L;
	*OutHeight = B - T;

	// create buffer
	pOutBuffer = GameCreateArray<unsigned char>(*OutWidth * *OutHeight);

	// draw them one by one, the later one will override the former one
	for (auto& data : UnionSHP_Data)
	{
		for (int j = data.Y - T; j < data.Height; ++j)
			for (int i = 0; i < data.Width; ++i)
				if (data.pBuffer[j * data.Width + i])
					pOutBuffer[j * *OutWidth + data.X - L + i] = data.pBuffer[j * data.Width + i];
				// memcpy_s(&pOutBuffer[j * *OutWidth + data.X - L], data.Width, &data.pBuffer[j * data.Width], data.Width);
		// after drawing, release the previous buffer
		GameDelete(data.pBuffer);
	}

	UnionSHP_Data.clear();
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