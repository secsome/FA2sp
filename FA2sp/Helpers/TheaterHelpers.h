#pragma once

#include "../FA2sp.h"

#include "Translations.h"
#include <MFC/ppmfc_cstring.h>
#include "STDHelpers.h"

#include <CLoading.h>
#include <CINI.h>

#include <set>
#include <vector>

class TheaterHelpers
{
public:

	static ppmfc::CString GetTranslatedName(ppmfc::CString theaterName)
	{
		if (!IsAllowedTheaterName(theaterName))
			return theaterName;

		auto itemName = "TheaterName" + GetSuffix(theaterName);
		return Translations::GetTranslationItem(itemName, FA2sp::Buffer) ? FA2sp::Buffer : theaterName;
	}

	static ppmfc::CString GetSuffix(ppmfc::CString theaterName)
	{
		if (strcmp(theaterName, "TEMPERATE") == 0)
			return "Tem";
		else if (strcmp(theaterName, "SNOW") == 0)
			return "Sno";
		else if (strcmp(theaterName, "URBAN") == 0)
			return "Urb";
		else if (strcmp(theaterName, "NEWURBAN") == 0)
			return "Ubn";
		else if (strcmp(theaterName, "LUNAR") == 0)
			return "Lun";
		else if (strcmp(theaterName, "DESERT") == 0)
			return "Des";
		else
			return "";
	}

	static bool IsAllowedTheaterName(ppmfc::CString theaterName)
	{
		std::set<ppmfc::CString> allowedNames = { "TEMPERATE", "SNOW", "URBAN", "NEWURBAN", "LUNAR", "DESERT" };
		std::set<ppmfc::CString> mdTheaterNames = { "NEWURBAN", "LUNAR", "DESERT" };

		if (!CLoading::HasMdFile && mdTheaterNames.find(theaterName) != mdTheaterNames.end())
			return false;

		if (allowedNames.find(theaterName) != allowedNames.end())
			return true;

		return false;
	}

	static std::vector<ppmfc::CString> GetEnabledTheaterNames()
	{
		std::vector<ppmfc::CString> list;

		if (auto sides = CINI::FAData->GetSection("Theaters"))
		{
			for (auto& itr : sides->GetEntities())
			{
				ppmfc::CString str = itr.second;

				if (STDHelpers::IsNullOrEmpty(str))
					continue;

				str.MakeUpper();
				str.Trim();

				if (IsAllowedTheaterName(str))
					list.push_back(str);
			}
		}

		if (list.size() > 0)
			return list;
		else
			return { "TEMPERATE", "SNOW", "URBAN", "NEWURBAN", "LUNAR", "DESERT" };
	}
};

