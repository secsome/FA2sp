#include "Body.h"

#include <Helpers/Macro.h>

#include <CMapData.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Ext/CMapData/Body.h"

DEFINE_HOOK(4D19A0, CMapValidator_DoValidator_Extra, 5)
{
	GET(CMapValidatorExt*, pThis, EDI);
	REF_STACK(BOOL, result, STACK_OFFS(0x200, 0x168));
	
	// Check for overlapped buildings
	{
		std::vector<int> Occupied;
		int length = CMapData::Instance->MapWidthPlusHeight;
		length *= length;
		Occupied.resize(length);

		if (auto pSection = CMapData::Instance->INI.GetSection("Structures"))
		{
			for (const auto& [_, Data] : pSection->GetEntities())
			{
				const auto splits = STDHelpers::SplitString(Data, 4);
				const int Index = CMapData::Instance->GetBuildingTypeID(splits[1]);
				const int Y = atoi(splits[3]);
				const int X = atoi(splits[4]);
				const auto& DataExt = CMapDataExt::BuildingDataExts[Index];
				
				if (!DataExt.IsCustomFoundation())
				{
					for (int dx = 0; dx < DataExt.Height; ++dx)
					{
						for (int dy = 0; dy < DataExt.Width; ++dy)
							++Occupied[CMapData::Instance->GetCoordIndex(X + dx, Y + dy)];
					}
				}
				else
				{
					for (const auto& block : *DataExt.Foundations)
						++Occupied[CMapData::Instance->GetCoordIndex(X + block.Y, Y + block.X)];
				}
			}
		}

		ppmfc::CString Format = pThis->FetchLanguageString(
			"MV_OverlapStructures", "%1 structures overlap at (%2, %3)");
		for (int i = 0; i < length; ++i)
		{
			if (Occupied[i] > 1)
			{
				result = FALSE;
				auto buffer = Format;
				buffer.ReplaceNumString(1, Occupied[i]);
				buffer.ReplaceNumString(2, CMapData::Instance->GetYFromCoordIndex(i));
				buffer.ReplaceNumString(3, CMapData::Instance->GetXFromCoordIndex(i));
				pThis->InsertString(buffer, false);
			}
		}
	}

	return 0;
}