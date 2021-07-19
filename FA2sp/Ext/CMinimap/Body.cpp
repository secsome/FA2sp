#include "Body.h"

void CMinimapExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x594EE0, &CMinimapExt::PreTranslateMessageExt);
}

BOOL CMinimapExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CView::PreTranslateMessage(pMsg);
}