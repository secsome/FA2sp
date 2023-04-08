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