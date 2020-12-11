#include "Body.h"

#include <FA2PP.h>
#include <Helpers/Macro.h>
#include <GlobalVars.h>

#include "../../FA2sp.h"

DEFINE_HOOK(51D3DE, ObjectBrowserControl_Redraw, 5)
{
    GET(CTreeCtrl*, pTree, ESI);
    GET(HTREEITEM, pParent, EDI);
    
    CSFDict* pCSF = reinterpret_cast<CSFDict*>(0x72A880);
	
    Logger::Debug("%d\n", pCSF->size());

    return 0;
}