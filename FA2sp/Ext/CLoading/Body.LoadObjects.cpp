#include "Body.h"

#include <GlobalVars.h>
#include <CINI.h>
#include <CMixFile.h>
#include <CShpFile.h>
#include <Drawing.h>
#include <CPalette.h>

#include "../../Helpers/MultimapHelper.h"

std::map<ppmfc::CString, CLoadingExt::ObjectType> CLoadingExt::ObjectTypes;

ppmfc::CString CLoadingExt::GetImageName(ppmfc::CString ID, int nFacing)
{
	MultimapHelper rules
	{
		&GlobalVars::INIFiles::Rules(),
		&GlobalVars::INIFiles::CurrentDocument()
	};
	auto& art = GlobalVars::INIFiles::Art();

	CLoadingExt* pLoading = (CLoadingExt*)GlobalVars::Dialogs::CLoading();
	switch (pLoading->GetItemType(ID))
	{
	case ObjectType::Infantry:
	{
		ppmfc::CString ImageID = pLoading->GetInfantryFileID(ID);
		ppmfc::CString DictName;
		DictName.Format("%s%d", ImageID, nFacing);
		return DictName;
	}
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
		MultimapHelper rules
		{
			&GlobalVars::INIFiles::Rules(),
			&GlobalVars::INIFiles::CurrentDocument()
		};

		auto load = [&rules](ppmfc::CString type, ObjectType e)
		{
			auto section = rules.GetSection(type);
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

	MultimapHelper rules
	{
		&GlobalVars::INIFiles::Rules(),
		&GlobalVars::INIFiles::CurrentDocument()
	};

	auto& art = GlobalVars::INIFiles::Art();

	ppmfc::CString ArtID;
	if (auto ppImage = rules.TryGetString(ID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = ID;

	auto eItemType = GetItemType(ID);
	switch (eItemType)
	{
	case CLoadingExt::ObjectType::Infantry:
		LoadInfantry(ID);
		break;
	case CLoadingExt::ObjectType::Terrain:
	case CLoadingExt::ObjectType::Smudge:
		LoadASSHP(ArtID);
		break;
	case CLoadingExt::ObjectType::Vehicle:
	case CLoadingExt::ObjectType::Aircraft:
		if (art.GetBool(ArtID, "Voxel"))
			LoadASVXL(ArtID);
		else
			LoadASSHP(ArtID);
		break;
	case CLoadingExt::ObjectType::Building:
		LoadBuilding(ID);
		break;
	case CLoadingExt::ObjectType::Unknown:
	default:
		break;
	}
}

int CLoadingExt::QueryPalettesISO(char identifier)
{
	switch (identifier)
	{
	case 'A':
		return this->PAL_ISOSNO;
	case 'U':
		return this->PAL_ISOURB;
	case 'N':
		return this->PAL_ISOUBN;
	case 'D':
		return this->PAL_ISODES;
	case 'L':
		return this->PAL_ISOLUN;
	case 'T':
	default:
		return this->PAL_ISOTEM;
	}
}

int CLoadingExt::QueryPalettesUNIT(char identifier)
{
	switch (identifier)
	{
	case 'A':
		return this->PAL_UNITSNO;
	case 'U':
		return this->PAL_UNITURB;
	case 'N':
		return this->PAL_UNITUBN;
	case 'D':
		return this->PAL_UNITDES;
	case 'L':
		return this->PAL_UNITLUN;
	case 'T':
	default:
		return this->PAL_UNITTEM;
	}
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
	MultimapHelper rules
	{
		&GlobalVars::INIFiles::Rules(),
		&GlobalVars::INIFiles::CurrentDocument()
	};

	ppmfc::CString ArtID;
	if (auto ppImage = rules.TryGetString(ID, "Image"))
		ArtID = *ppImage;
	else
		ArtID = ID;

	ppmfc::CString ImageID = GlobalVars::INIFiles::Art->GetString(ArtID, "Image", ArtID);

	if (rules.GetBool(ID, "AlternateTheaterArt"))
		ImageID += this->TheaterIdentifier;
	else if (rules.GetBool(ID, "AlternateArcticArt"))
		if (this->TheaterIdentifier == 'A')
			ImageID += 'A';
	if (!GlobalVars::INIFiles::Art->SectionExists(ImageID))
		ImageID = ArtID;

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
		unsigned char* FramesBuffers[8];
		CMixFile::LoadSHP(FileName, nMix);
		CShpFile::GetSHPHeader(&header);
		for (int i = 0; i < 8; ++i)
		{
			CShpFile::LoadFrame(framesToRead[i], 1, &FramesBuffers[i]);
			ppmfc::CString DictName;
			DictName.Format("%s%d", ImageID, i);
			SetImageData(FramesBuffers[i], DictName, header.Width, header.Height);
		}
	}
}

void CLoadingExt::LoadASSHP(ppmfc::CString ArtID)
{
	

	
	
}

void CLoadingExt::LoadASVXL(ppmfc::CString ArtID)
{
}

void CLoadingExt::SetImageData(unsigned char* pBuffer, ppmfc::CString NameInDict, int FullWidth, int FullHeight)
{
	auto pData = ImageDataMapHelper::GetImageDataFromMap(NameInDict);
	unsigned char* pCompressedBuffer = nullptr;
	int nWidth, nHeight;

	ShrinkSHP(pBuffer, FullWidth, FullHeight, pCompressedBuffer, &nWidth, &nHeight);

	pData->pImageBuffer = pCompressedBuffer;
	SetValidBuffer(pData, nWidth, nHeight);
	pData->Flag = ImageDataFlag::SHP;
	pData->IsOverlay = false;
	pData->pPalette = Palette::PALETTE_UNIT;
	pData->ValidX = 0;
	pData->ValidY = 0;
	pData->ValidHeight = pData->FullHeight = nHeight;
	pData->ValidWidth = pData->FullWidth = nWidth;

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