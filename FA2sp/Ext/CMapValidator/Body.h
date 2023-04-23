#pragma once

#include <CMapValidator.h>

#include <unordered_set>

class CMapValidatorExt : public CMapValidator
{
public:
	void ValidateStructureOverlapping(BOOL& result);
	void ValidateMissingParams(BOOL& result);

	ppmfc::CString FetchLanguageString(const char* Key, const char* def);
	void InsertString(const char* String, bool IsWarning);

	static std::unordered_set<std::string> StructureOverlappingIgnorance;
};