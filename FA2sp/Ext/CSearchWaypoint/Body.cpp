#include "Body.h"

CSearchWaypoint* CSearchWaypointExt::Instance = nullptr;

void CSearchWaypointExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x596238, &CSearchWaypointExt::PreTranslateMessageExt);
}

BOOL CSearchWaypointExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}