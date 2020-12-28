#pragma once

#include "../FA2sp.h"
#include "../Logger.h"

#include <Helpers/Macro.h>


// Load our own accelerators
// Notice, our accelerator's id need to be the same as FA2's
#ifdef _DEBUG
#undef _DEBUG

DEFINE_HOOK(41FAFD, LoadAccelerators_sub_41FAD0, 7)
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
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
#ifdef _DEBUG
	if (IS_INTRESOURCE(lpName)) {
		Logger::Debug(__FUNCTION__" lpName ID = %d\n", LOWORD(lpName));
	}
	else {
		Logger::Debug(__FUNCTION__" lpName = %s\n", lpName);
	}
#endif
	if (HRSRC hResInfo = FindResource(hModule, lpName, lpType)) {
		if (HGLOBAL hResData = LoadResource(hModule, hResInfo)) {
			LockResource(hResData);
			R->EDI(hResData);
			return 0x554CAA;
		}
	}
	return 0;
}

#define _DEBUG
#endif