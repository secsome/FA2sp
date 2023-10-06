#include "Body.h"

#include <Drawing.h>
#include <CFinalSunApp.h>
#include <CMixFile.h>
#include <CLoading.h>
#include <CINI.h>
#include "..\..\Miscs\Palettes.h"
#include "..\CMapData\Body.h"

DEFINE_HOOK(486B00, CLoading_InitMixFiles, 7)
{
	GET(CLoadingExt*, pThis, ECX);

	bool result = pThis->InitMixFilesFix();
	R->EAX(result);

	if (!result)
	{
		MessageBox(NULL, "Failed to load necessary mix file!", "Fatal Error!", MB_OK);
		ExitProcess(114514);
	}

	return 0x48A26A;
}

DEFINE_HOOK(48A650, CLoading_SearchFile, 6)
{
	GET(CLoadingExt*, pThis, ECX);
	GET_STACK(const char*, Filename, 0x4);
	GET_STACK(unsigned char*, pTheaterType, 0x8);
	
	for (int i = 0; i < CMixFile::ArraySize; ++i)
	{
		auto& mix = CMixFile::Array[i];
		if (!mix.is_open())
			break;
		if (CMixFile::HasFile(Filename, i + 1))
		{
#ifndef NDEBUG
			Logger::Debug("[SearchFile] %s - %d\n", Filename, i + 1);
#endif
			R->EAX(i + 1);
			return 0x48AA63;
		}
	}

#ifndef NDEBUG
	Logger::Debug("[SearchFile] %s - NOT FOUND\n", Filename);
#endif
	R->EAX(0);
	return 0x48AA63;
}

DEFINE_HOOK(49DD64, CMapData_LoadMap_InitMixFiles_Removal, 5)
{
	CLoading::Instance->CSCBuiltby.~CStatic();
	CLoading::Instance->CSCLoading.~CStatic();
	CLoading::Instance->CSCVersion.~CStatic();
	CLoading::Instance->CPCProgress.~CProgressCtrl();
	struct CLoadingHelper
	{
		void DTOR()
		{
			JMP_STD(0x551A1D);
		}
	};
	reinterpret_cast<CLoadingHelper*>(CLoading::Instance())->DTOR();
	return 0x49DD74;
}

DEFINE_HOOK(4B8CFC, CMapData_CreateMap_InitMixFiles_Removal, 5)
{
	CLoading::Instance->CSCBuiltby.~CStatic();
	CLoading::Instance->CSCLoading.~CStatic();
	CLoading::Instance->CSCVersion.~CStatic();
	CLoading::Instance->CPCProgress.~CProgressCtrl();
	struct CLoadingHelper
	{
		void DTOR()
		{
			JMP_STD(0x551A1D);
		}
	};
	reinterpret_cast<CLoadingHelper*>(CLoading::Instance())->DTOR();
	return 0x4B8D0C;
}


DEFINE_HOOK(4903F3, CLoading_DrawOverlay_Palette, 7) 
{
	GET(CLoadingExt*, pThis, EDI);
	REF_STACK(ImageDataClass, pDrawData, STACK_OFFS(0x1C8, 0xC8));
	GET_STACK(int, nOverlayIndex, STACK_OFFS(0x1C8, -0x8));

	if (nOverlayIndex >= 0 && nOverlayIndex < 255)
	{
		auto const& typeData = CMapDataExt::OverlayTypeDatas[nOverlayIndex];

		if (typeData.Wall)
		{
			auto palName = typeData.PaletteName;
			pThis->GetFullPaletteName(palName);
			pDrawData.pPalette = PalettesManager::LoadPalette(palName);
		}
	}

	return 0;
}
