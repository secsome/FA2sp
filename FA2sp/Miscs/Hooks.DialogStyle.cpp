#include <Helpers/Macro.h>

// DEFINE_HOOK(54FC1E, CFileDialog_EnableExplorerStyle, 7)
// {
//     GET(CFileDialog*, pDialog, ESI);
// 
//     OPENFILENAME ofn = pDialog->m_ofn;
// 
//     ofn.Flags &= ~OFN_ENABLEHOOK;
// 
//     if (ofn.pvReserved)
//         R->EAX(GetOpenFileNameA(&ofn));
//     else
//         R->EAX(GetSaveFileNameA(&ofn));
// 
//     return 0x54FC37;
// }