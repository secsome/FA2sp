#include "Body.h"

CMinimap* CMinimapExt::Instance = nullptr;

void CMinimapExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CMinimapExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x594EE0, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CMinimapExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CView::PreTranslateMessage(pMsg);
}