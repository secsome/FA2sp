//#include <FA2PP.h>
//#include <Helpers/Macro.h>
//
//static HTREEITEM hTreeItems[64];
//
//DEFINE_HOOK(51D3DE, ObjectBrowserControl_Redraw, 5)
//{
//    GET(CTreeCtrl*, pTree, ESI);
//    GET(HTREEITEM, pParent, EDI);
//    hTreeItems[0] =
//        pTree->InsertItem(5, "Allied", 0, 0, 0, 0, -1, pParent, TVI_LAST);
//    hTreeItems[1] =
//        pTree->InsertItem(5, "Soviet", 0, 0, 0, 0, -1, pParent, TVI_LAST);
//    hTreeItems[2] =
//        pTree->InsertItem(5, "Epsilon", 0, 0, 0, 0, -1, pParent, TVI_LAST);
//    hTreeItems[3] =
//        pTree->InsertItem(5, "Others", 0, 0, 0, 0, -1, pParent, TVI_LAST);
//    return 0x51D6FC;
//}