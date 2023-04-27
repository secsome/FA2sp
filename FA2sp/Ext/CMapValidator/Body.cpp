#include "Body.h"

#include "../../Helpers/Translations.h"
#include "../../Helpers/STDHelpers.h"
#include "../../Ext/CMapData/Body.h"
#include "../../FA2sp.h"

#include <CMapData.h>

std::unordered_set<std::string> CMapValidatorExt::StructureOverlappingIgnores;

void CMapValidatorExt::ValidateStructureOverlapping(BOOL& result)
{
	std::vector<std::vector<std::string>> Occupied;
	int length = CMapData::Instance->MapWidthPlusHeight;
	length *= length;
	Occupied.resize(length);

	if (auto pSection = CMapData::Instance->INI.GetSection("Structures"))
	{
		for (const auto& [_, Data] : pSection->GetEntities())
		{
			const auto splits = STDHelpers::SplitString(Data, 4);

			// In the list, ignore it.
			if (StructureOverlappingIgnores.count(splits[1].m_pchData))
				continue;

			const int Index = CMapData::Instance->GetBuildingTypeID(splits[1]);
			const int Y = atoi(splits[3]);
			const int X = atoi(splits[4]);
			const auto& DataExt = CMapDataExt::BuildingDataExts[Index];

			if (!DataExt.IsCustomFoundation())
			{
				for (int dx = 0; dx < DataExt.Height; ++dx)
				{
					for (int dy = 0; dy < DataExt.Width; ++dy)
						Occupied[CMapData::Instance->GetCoordIndex(X + dx, Y + dy)].emplace_back(splits[1].m_pchData);
				}
			}
			else
			{
				for (const auto& block : *DataExt.Foundations)
					Occupied[CMapData::Instance->GetCoordIndex(X + block.Y, Y + block.X)].emplace_back(splits[1].m_pchData);
			}
		}
	}

	ppmfc::CString Format = this->FetchLanguageString(
		"MV_OverlapStructures", "%1 structures overlap at (%2, %3): ");
	for (int i = 0; i < length; ++i)
	{
		if (Occupied[i].size() > 1)
		{
			if (!ExtConfigs::ExtendedValidationNoError)
				result = FALSE;
			auto buffer = Format;
			buffer.ReplaceNumString(1, Occupied[i].size());
			buffer.ReplaceNumString(2, CMapData::Instance->GetYFromCoordIndex(i));
			buffer.ReplaceNumString(3, CMapData::Instance->GetXFromCoordIndex(i));
			for (size_t k = 0; k < Occupied[i].size() - 1; ++k)
			{
				buffer += Occupied[i][k].c_str();
				buffer += ", ";
			}
			buffer += Occupied[i].back().c_str();
			this->InsertStringAsError(buffer);
		}
	}
}

void CMapValidatorExt::ValidateMissingParams(BOOL& result)
{
	auto ValidateSection = [&](const char* section)
	{
		if (auto pSection = CMapData::Instance->INI.GetSection(section))
		{
			ppmfc::CString Format = this->FetchLanguageString(
				"MV_LogicMissingParams", "%1 - %2 may has a missing param! Please have a check on it.");
			Format.ReplaceNumString(1, section);

			for (const auto& [key, value] : pSection->GetEntities())
			{
				if (value.Find(",,") != -1) // has missing param!
				{
					if (!ExtConfigs::ExtendedValidationNoError)
						result = FALSE;
					auto tmp = Format;
					tmp.ReplaceNumString(2, key);
					InsertStringAsError(tmp);
				}
			}
		}
	};

	ValidateSection("Triggers");
	ValidateSection("Actions");
	ValidateSection("Events");
	ValidateSection("Tags");
}

ppmfc::CString CMapValidatorExt::FetchLanguageString(const char* Key, const char* def)
{
	ppmfc::CString buffer;

	if (!Translations::GetTranslationItem(Key, buffer))
		buffer = def;

	return buffer;
}

void CMapValidatorExt::InsertStringAsError(const char* String)
{
	CLCResults.InsertItem(LVIF_TEXT | LVIF_IMAGE, CLCResults.GetItemCount(), String, NULL, NULL, ExtConfigs::ExtendedValidationNoError, NULL);
}

void CMapValidatorExt::InsertString(const char* String, bool IsWarning)
{
	CLCResults.InsertItem(LVIF_TEXT | LVIF_IMAGE, CLCResults.GetItemCount(), String, NULL, NULL, IsWarning, NULL);
}