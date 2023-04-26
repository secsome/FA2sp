#include "Body.h"

#include <Helpers/Macro.h>

#include <CMapData.h>

DEFINE_HOOK(4D19A0, CMapValidator_DoValidator_Extra, 5)
{
	GET(CMapValidatorExt*, pThis, EDI);
	REF_STACK(BOOL, result, STACK_OFFS(0x200, 0x168));
	
	pThis->ValidateStructureOverlapping(result);
	pThis->ValidateMissingParams(result);

	return 0;
}

DEFINE_HOOK(4CEA50, CMapValidator_CTOR, 7)
{
	if (auto pSection = CINI::FAData->GetSection("StructureOverlappingCheckIgnores"))
	{
		for (const auto& [key, value] : pSection->GetEntities())
			CMapValidatorExt::StructureOverlappingIgnores.emplace(std::string{value.m_pchData});
	}

	return 0;
}

DEFINE_HOOK(426A60, CMapValidator_DTOR, 7)
{
	CMapValidatorExt::StructureOverlappingIgnores.clear();

	return 0;
}