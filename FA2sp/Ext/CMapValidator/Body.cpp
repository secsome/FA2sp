#include "Body.h"

#include "../../Helpers/Translations.h"

#include <CMapData.h>

ppmfc::CString CMapValidatorExt::FetchLanguageString(const char* Key, const char* def)
{
	ppmfc::CString buffer;

	if (!Translations::GetTranslationItem(Key, buffer))
		buffer = def;

	return buffer;
}

void CMapValidatorExt::InsertString(const char* String, bool IsWarning)
{
	CLCResults.InsertItem(LVIF_TEXT | LVIF_IMAGE, CLCResults.GetItemCount(), String, NULL, NULL, IsWarning, NULL);
}