#include "Body.h"

CTaskForce* CTaskForceExt::Instance = nullptr;

void CTaskForceExt::ProgramStartupInit()
{
	Logger::Debug(__FUNCTION__"\n");
	auto constexpr taskforceCBMemberTypeMsg = CBN_KILLFOCUS;
	auto PreTranslateAddr = &CTaskForceExt::PreTranslateMessageExt;

	RunTime::ResetMemoryContentAt(0x596B50 + sizeof(taskforceCBMemberTypeMsg), &taskforceCBMemberTypeMsg, sizeof(taskforceCBMemberTypeMsg));
	RunTime::ResetMemoryContentAt(0x596C88, &PreTranslateAddr, sizeof(PreTranslateAddr));

}

BOOL CTaskForceExt::PreTranslateMessageExt(MSG* pMsg)
{
	switch (pMsg->message) {
	case WM_KEYDOWN: {
		switch (pMsg->wParam) {
		case VK_RETURN: {
			return TRUE; // Hey, we've processed it, don't exit!
		}
		default:
			break;
		}
		break;
	}
	case WM_KILLFOCUS: {
		auto pEdit = this->CCBMemberType.GetWindow(GW_CHILD);
		if (pMsg->hwnd == pEdit->m_hWnd) {
			this->OnMemberEditChanged();
		}
		break;
	}

	default:
		break;
	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

#if 0
bool IsMemberTypeSelectedFromBox = false;
//now this one is used as "focus loss" handler
DEFINE_HOOK(4E44C7, CTaskForce_OnMemberEditChanged, 7)
{
	GET(CTaskForce* const, pThis, ESI);
	GET_STACK(const char*, pStr, 0x28);

	Logger::g_Logger.Info(std::string(__FUNCTION__));
	Logger::g_Logger.Info(pStr);

	pThis->UpdateMemberType();
	pThis->CCBMemberType.SetWindowTextA(pStr);

	return 0x4E44DA;
}
#endif

#if 0
DEFINE_HOOK(4E4540, CTaskForce_OnMemberSelectChanged, 7)
{
	GET(CTaskForce* const, pThis, ECX);

	Logger::g_Logger.Info(std::string(__FUNCTION__));
	pThis->OnMemberEditChanged();

	return 0x4E489A;
}

DEFINE_HOOK(4E4846, CTaskForce_OnMemberSelectChanged_Update, 7)
{
	GET(CTaskForce* const, pThis, ESI);
	GET_STACK(const char*, pStr, 0x20);

	Logger::g_Logger.Info(std::string(__FUNCTION__));
	Logger::g_Logger.Info(pStr);

	pThis->UpdateMemberType();
	//pThis->CCBMemberType.SetWindowTextA(pStr);
	IsMemberTypeSelectedFromBox = true;

	return 0x4E484D;
}

DEFINE_HOOK(4E358D, CTaskForce_OnItemListSelect_MemberType, C)
{
	GET(const char*, pStr, EAX);

	Logger::g_Logger.Info(std::string(__FUNCTION__));
	Logger::g_Logger.Info(pStr);

	return 0;
}

DEFINE_HOOK(4E1F7A, CTaskForce_UpdateMemberType, 8)
{
	GET_STACK(DWORD, caller, 0x128);
	GET(const char*, pStr, EDX);
	char buffer[0x20];
	sprintf_s(buffer, "%08X", caller);
	Logger::g_Logger.Info(__FUNCTION__" caller = " + std::string(buffer));
	Logger::g_Logger.Info(pStr);

	return 0;
}
#endif