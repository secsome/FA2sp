#pragma once

#include <CLoading.h>
#include "../FA2Expand.h"

#include <vector>
#include <map>

class ImageDataClass;
class Palette;

class NOVTABLE CLoadingExt : public CLoading
{
public:

	//hook function to replace in virtual function map
	//BOOL PreTranslateMessageExt(MSG* pMsg);

	//static void ProgramStartupInit();

	void LoadObjects(ppmfc::CString pRegName);
	static ppmfc::CString GetImageName(ppmfc::CString ID, int nFacing);
	static void ClearItemTypes();
private:
	void GetFullPaletteName(ppmfc::CString& PaletteName);
	static ppmfc::CString* __cdecl GetDictName(ppmfc::CString* ret, const char* ID, int nFacing) { JMP_STD(0x475450); }
	static ppmfc::CString GetDictName(ppmfc::CString ID, int nFacing)
	{
		ppmfc::CString buffer;
		GetDictName(&buffer, ID, nFacing);
		return buffer;
	}

	void LoadBuilding(ppmfc::CString ID);
	void LoadInfantry(ppmfc::CString ID);
	void LoadTerrainOrSmudge(ppmfc::CString ID);
	void LoadVehicleOrAircraft(ppmfc::CString ID);

	void SetImageData(unsigned char* pBuffer, ppmfc::CString NameInDict, int FullWidth, int FullHeight, Palette* pPal);
	void SetImageData(unsigned char* pBuffer, ImageDataClass* pData, int FullWidth, int FullHeight, Palette* pPal);
	void ShrinkSHP(unsigned char* pIn, int InWidth, int InHeight, unsigned char*& pOut, int* OutWidth, int* OutHeight);
	void UnionSHP_Add(unsigned char* pBuffer, int Width, int Height, int DeltaX = 0, int DeltaY = 0, bool UseTemp = false);
	void UnionSHP_GetAndClear(unsigned char*& pOutBuffer, int* OutWidth, int* OutHeight, bool UseTemp = false);
	void VXL_Add(unsigned char* pCache, int X, int Y, int Width, int Height);
	void VXL_GetAndClear(unsigned char*& pBuffer, int* OutWidth, int* OutHeight);
	
	void SetValidBuffer(ImageDataClass* pData, int Width, int Height);

	enum class ObjectType{
		Unknown = -1,
		Infantry = 0,
		Vehicle = 1,
		Aircraft = 2,
		Building = 3,
		Terrain = 4,
		Smudge = 5
	};

	ppmfc::CString GetArtID(ppmfc::CString ID);
	ppmfc::CString GetVehicleOrAircraftFileID(ppmfc::CString ID);
	ppmfc::CString GetTerrainOrSmudgeFileID(ppmfc::CString ID);
	ppmfc::CString GetBuildingFileID(ppmfc::CString ID);
	ppmfc::CString GetInfantryFileID(ppmfc::CString ID);
	ObjectType GetItemType(ppmfc::CString ID);

	void DumpFrameToFile(unsigned char* pBuffer, Palette* pPal, int Width, int Height, ppmfc::CString name);
	
	struct SHPUnionData
	{
		unsigned char* pBuffer;
		int Width;
		int Height;
		int DeltaX;
		int DeltaY;
	};
	
	static std::vector<SHPUnionData> UnionSHP_Data[2];
	static std::map<ppmfc::CString, ObjectType> ObjectTypes;
	static unsigned char VXL_Data[0x10000];
};