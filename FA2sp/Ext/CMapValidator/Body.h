#pragma once

#include <CMapValidator.h>

class CMapValidatorExt : public CMapValidator
{
public:
	ppmfc::CString FetchLanguageString(const char* Key, const char* def);
	void InsertString(const char* String, bool IsWarning);
};