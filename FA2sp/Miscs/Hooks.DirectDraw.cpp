#include <Helpers/Macro.h>

#include <CLoading.h>
#include <CFinalSunApp.h>
#include <CFinalSunDlg.h>
#include <CIsoView.h>

#include "../Logger.h"
#include "../FA2sp.h"

DEFINE_HOOK(490EF0, CLoading_InitializeDDraw, 6)
{
	static constexpr GUID _IID_IDirectDraw4 =
	{
		0x9c59509a, 0x39bd, 0x11d1,
		{ 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5 }
	};
	static constexpr GUID _IID_IDirectDraw7 =
	{
		0x15e65ec0, 0x3b9c, 0x11d2,
		{ 0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b }
	};

	static GUID* pIID_DirectDrawEmulation = (GUID*)2;

	GET(CLoading*, pThis, ECX);

	CFinalSunDlg::Instance->LastSucceededOperation = 7;

	Logger::Raw(
		"\n"
		"=====================================\n"
		"DirectDrawCreate() will be called now\n"
	);

	HRESULT hr = S_OK;
	auto pIsoView = reinterpret_cast<CFinalSunDlg*>(CFinalSunApp::Instance->m_pMainWnd)->MyViewFrame.pIsoView;
	HRESULT(WINAPI **ppDirectDrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*) = decltype(ppDirectDrawCreate)(0x591030);

	hr = (*ppDirectDrawCreate)(ExtConfigs::DDrawEmulation ? pIID_DirectDrawEmulation : nullptr, &pIsoView->lpDirectDraw, nullptr);
	if (FAILED(hr))
	{
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox("DirectDraw could not be initialized! Quitting...");
		exit(-1);
	}
	Logger::Raw("DirectDrawCreate() successful\n");

	pThis->CPCProgress.SetPos(1);
	pThis->UpdateWindow();

	Logger::Raw("Now querying the DirectX 7 or 6 interface\n");

	hr = pIsoView->lpDirectDraw->QueryInterface(_IID_IDirectDraw7, reinterpret_cast<LPVOID*>(&pIsoView->lpDD7));
	if (FAILED(hr))
	{
		Logger::Raw("QueryInterface() failed -> Using DirectX 6.0\n");
		hr = pIsoView->lpDirectDraw->QueryInterface(_IID_IDirectDraw4, reinterpret_cast<LPVOID*>(&pIsoView->lpDD7));
		if (FAILED(hr))
		{
			pThis->ShowWindow(SW_HIDE);
			pThis->MessageBox("You need at least DirectX 6.0 to run this program", "Error");
			exit(-1);
		}
	}

	Logger::Raw(
		"QueryInterface() successful\n"
		"Now setting cooperative level\n"
	);

	hr = pIsoView->lpDD7->SetCooperativeLevel(pIsoView->m_hWnd, DDSCL_NOWINDOWCHANGES | DDSCL_NORMAL);
	if (FAILED(hr))
	{
		Logger::Raw("SetCooperativeLevel() failed\n");
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox("Cooperative Level could not be set!Quitting...");
		exit(-2);
	}

	Logger::Raw(
		"SetCooperativeLevel() successful\n"
		"Creating primary surface\n"
	);

	pThis->CPCProgress.SetPos(2);
	pThis->UpdateWindow();

	DDSURFACEDESC2 dds = { 0 };
	dds.dwSize = sizeof(dds);
	// In system memory to speedup the lock & unlock operations
	dds.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if (!ExtConfigs::DDrawInVideoMem)
		dds.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	dds.dwFlags = DDSD_CAPS;

	// Try 300 times at max!
	for (int i = 0; i <= 300; ++i)
	{
		hr = pIsoView->lpDD7->CreateSurface(&dds, &pIsoView->lpDDPrimarySurface, nullptr);
		Logger::Raw("Return code: 0x%x\n", hr);

		if (FAILED(hr))
		{
			if (i == 300)
			{
				Logger::Raw("CreateSurface() failed\n");
				pThis->ShowWindow(SW_HIDE);
				pThis->MessageBox("Primary surface could not be initialized! Quitting...");
				pIsoView->lpDD7->Release();
				pIsoView->lpDD7 = nullptr;
				exit(-3);
			}
			Sleep(50);
		}
		else
			break;
	}

	DDPIXELFORMAT ddpf = { 0 };
	ddpf.dwSize = sizeof(ddpf);
	pIsoView->lpDDPrimarySurface->GetPixelFormat(&ddpf);
	if (!ddpf.dwBBitMask || !ddpf.dwRBitMask || !ddpf.dwGBitMask)
	{
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox(
			"You must not use a palette color mode like 8 bit in order to run FinalAlert 2(tm). Please check readme.txt"
			"Error"
		);
	}

	// Set PixelSizeInBytes
	*reinterpret_cast<DWORD*>(0x72A8C0) = (ddpf.dwRGBBitCount + 7) >> 3;

	Logger::Raw(
		"CreateSurface() successful\n"
		"Creating backbuffer surface\n"
	);

	ZeroMemory(&dds, sizeof(dds));
	dds.dwSize = 0x7C;
	dds.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	pIsoView->lpDDPrimarySurface->GetSurfaceDesc(&dds);
	// In system memory to speedup the lock & unlock operations
	dds.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	if (!ExtConfigs::DDrawInVideoMem)
		dds.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	dds.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	
	hr = pIsoView->lpDD7->CreateSurface(&dds, &pIsoView->lpDDBackBufferSurface, nullptr);
	if (FAILED(hr))
	{
		Logger::Raw("CreateSurface() failed\n");
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox("Backbuffer surface could not be initialized! Quitting...");
		pIsoView->lpDDPrimarySurface->Release();
		pIsoView->lpDDPrimarySurface = nullptr;
		pIsoView->lpDD7->Release();
		pIsoView->lpDD7 = nullptr;
		exit(-4);
	}

	hr = pIsoView->lpDD7->CreateSurface(&dds, &pIsoView->lpDDTempBufferSurface, nullptr);
	if (FAILED(hr))
	{
		Logger::Raw("CreateSurface() failed\n");
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox("Tempbuffer surface could not be initialized! Quitting...");
		pIsoView->lpDDBackBufferSurface->Release();
		pIsoView->lpDDBackBufferSurface = nullptr;
		pIsoView->lpDDPrimarySurface->Release();
		pIsoView->lpDDPrimarySurface = nullptr;
		pIsoView->lpDD7->Release();
		pIsoView->lpDD7 = nullptr;
		exit(-4);
	}

	Logger::Raw(
		"CreateSurface() successful\n"
		"Now creating clipper\n"
	);

	LPDIRECTDRAWCLIPPER lpClipper;
	hr = pIsoView->lpDD7->CreateClipper(NULL, &lpClipper, nullptr);
	if (FAILED(hr))
	{
		Logger::Raw("CreateClipper() failed\n");
		pThis->ShowWindow(SW_HIDE);
		pThis->MessageBox("Clipper could not be created! Quitting...");
		pIsoView->lpDDTempBufferSurface->Release();
		pIsoView->lpDDTempBufferSurface = nullptr;
		pIsoView->lpDDBackBufferSurface->Release();
		pIsoView->lpDDBackBufferSurface = nullptr;
		pIsoView->lpDDPrimarySurface->Release();
		pIsoView->lpDDPrimarySurface = nullptr;
		pIsoView->lpDD7->Release();
		pIsoView->lpDD7 = nullptr;
	}

	Logger::Raw(
		"CreateClipper() successful\n"
		"=====================================\n\n"
	);

	pIsoView->lpDDPrimarySurface->SetClipper(lpClipper);
	lpClipper->SetHWnd(NULL, pIsoView->m_hWnd);

	return 0x49192F;
}