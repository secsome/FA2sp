#pragma once

#include "UIColor.h"

#include "../FA2sp.h"
#include "../Logger.h"

#include <FA2PP.h>

// Load our own accelerators
// Notice, our accelerator's id need to be the same as FA2's

DEFINE_HOOK(41FAFD, LoadAccelerators_CFinalSunApp_InitInstance, 7)
{
	const HINSTANCE hInstance = static_cast<HINSTANCE>(FA2sp::hInstance);
	R->EAX<HINSTANCE>(hInstance);
	return 0;
}

// Replace the resources

DEFINE_HOOK(56543B, FetchResource_CToolBar_LoadBitmapA, 6)
{
	GET_STACK(LPCSTR, lpName, STACK_OFFS(0xC, -4));
	const LPCSTR lpType = RT_BITMAP;
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		HBITMAP hBitmap = AfxLoadSysColorBitmap(hModule, hResInfo, 0);
		R->EBX(hResInfo);
		R->ESI(hModule);
		return 0x565457;
	}
	return 0;
}

DEFINE_HOOK(551B07, FetchResource_Cwnd_CreateDlg, 6)
{
	GET_STACK(LPCSTR, lpName, STACK_OFFS(0xC, -4));
	const LPCSTR lpType = RT_DIALOG;
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			LockResource(hResData);
			R->EAX(hResData);
			return 0x551B27;
		}
	}
	return 0;
}

DEFINE_HOOK(551A82, FetchResource_CDialog_Create, 5)
{
	GET(LPCSTR, lpName, EBX);
	const LPCSTR lpType = RT_DIALOG;
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			R->ESI(hModule);
			R->EAX(hResData);
			return 0x551A97;
		}
	}
	return 0;
}

DEFINE_HOOK(552147, FetchResource_CDialog_CheckAutoCenter, 5)
{
	const LPCSTR lpName = *(LPCSTR*)(R->EDI() + 0x40);
	const LPCSTR lpType = RT_DIALOG;
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			R->EAX(hResInfo);
			R->EBX(hModule);
			return 0x55215B;
		}
	}
	return 0;
}

DEFINE_HOOK(56537B, FetchResource_CToolBar_LoadToolBar, 5)
{
	GET_BASE(LPCSTR, lpName, 0x8);
	const LPCSTR lpType = (LPCSTR)(0xF1);
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			LockResource(hResData);
			R->ESI(hResData);
			return 0x5653A1;
		}
	}
	return 0;
}

DEFINE_HOOK(551E57, FetchResource_CDialog_DoModal, 5)
{
	const LPCSTR lpName = *(LPCSTR*)(R->ESI() + 0x40);
	const LPCSTR lpType = RT_DIALOG;
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			R->EBX(hModule);
			R->EDI(hResData);
			return 0x551E6D;
		}
	}
	return 0;
}

DEFINE_HOOK(554C8A, FetchResource_Cwnd_ExecuteDlgInit, 5)
{
	GET_STACK(LPCSTR, lpName, STACK_OFFS(0xC, -4));
	const LPCSTR lpType = (LPCSTR)(0xF0);
	const HMODULE hModule = static_cast<HMODULE>(FA2sp::hInstance);
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			LockResource(hResData);
			R->EDI(hResData);
			return 0x554CAA;
		}
	}
	return 0;
}

//DEFINE_HOOK(5521AA, CDialog_OnCtlColor, 8)
//{
//	GET(CDialog*, pThis, ECX);
//	GET_STACK(CDC*, pDC, 0x4);
//	GET_STACK(CWnd*, pWnd, 0x8);
//	GET_STACK(UINT, nCtlColor, 0xC);
//
//	switch (nCtlColor)
//	{
//	case CTLCOLOR_BTN:
//	case CTLCOLOR_EDIT:
//	case CTLCOLOR_LISTBOX:
//	case CTLCOLOR_MSGBOX:
//	case CTLCOLOR_SCROLLBAR:
//	case CTLCOLOR_MAX:
//		return 0;
//	case CTLCOLOR_STATIC:
//	{
//		return 0;
//		/*Logger::Debug("LINEED! res = %d\n", pDC->LineTo(5, 5));
//		RECT rect;
//		pWnd->GetClientRect(&rect);
//		Logger::Debug("Client Rect = %d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
//		pWnd->GetWindowRect(&rect);
//		Logger::Debug("Window Rect = %d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);
//		Logger::Debug("HDC = %p\n", pDC->GetSafeHdc());
//		R->EAX<HBRUSH>((HBRUSH)GetStockObject(HOLLOW_BRUSH));
//		return 0x5521BB;*/
//	}
//	case CTLCOLOR_DLG:
//		pDC->MoveTo(0, 0);
//		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetBkColor(RGB(124, 0, 0));
//		RECT rect;
//		pWnd->GetWindowRect(&rect);
//		pDC->LineTo(100, 100);
//		pDC->DrawText("NMSLLLL", &rect, DT_CALCRECT);
//		R->EAX<HBRUSH>((HBRUSH)GetStockObject(HOLLOW_BRUSH));
//		//R->EAX(CreateSolidBrush(RGB(0, 0, 0)));
//		return 0x5521BB;
//	default:
//		return 0;
//	}
//}

// Customize Control Background Colors
/*
HBRUSH FA2sp::hBrush = NULL;
DEFINE_HOOK(554901, CWnd_OnCtlColor, 6)
{
	GET(CWnd*, pThis, ECX);
	GET_STACK(CDC*, pDC, 0x4);
	GET_STACK(CWnd*, pWnd, 0x8);
	GET_STACK(UINT, nCtlColor, 0xC);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_MAX:
	case CTLCOLOR_STATIC:

		//return 0x554925;
	default:
		return 0;
	}
}

DEFINE_HOOK(5521AA, CDialog_OnCtlColor, 8)
{
	GET(CDialog*, pThis, ECX);
	GET_STACK(CDC*, pDC, 0x4);
	GET_STACK(CWnd*, pWnd, 0x8);
	GET_STACK(UINT, nCtlColor, 0xC);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_MAX:
	case CTLCOLOR_STATIC:

		//return 0x5521BB;
	default:
		return 0;
	}
}

DEFINE_HOOK(55F086, CControlBar_OnCtlColor, 7)
{
	GET(CControlBar*, pThis, ECX);
	GET_STACK(CDC*, pDC, 0x4);
	GET_STACK(CWnd*, pWnd, 0x8);
	GET_STACK(UINT, nCtlColor, 0xC);

	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_MAX:
	case CTLCOLOR_STATIC:

		//return 0x55F0DB;
	default:
		return 0;
	}
}
*/