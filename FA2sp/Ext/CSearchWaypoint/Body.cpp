#include "Body.h"

CSearchWaypoint* CSearchWaypointExt::Instance = nullptr;

void CSearchWaypointExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto PreTranslateAddr = &CSearchWaypointExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596238, &PreTranslateAddr, sizeof(PreTranslateAddr));
}

BOOL CSearchWaypointExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}