#pragma once

extern "C"
{
	__declspec(dllimport) void* __stdcall CncImgMalloc(unsigned int sz);
	__declspec(dllimport) void __stdcall CncImgFree(void* ptr);

	__declspec(dllimport) void __stdcall CncImgCreate();
	__declspec(dllimport) void __stdcall CncImgRelease();

	__declspec(dllimport) void __stdcall CncImgSetMaxFacing(unsigned int nFacingCount);
	__declspec(dllimport) unsigned int __stdcall CncImgGetMaxFacing();

	__declspec(dllimport) bool __stdcall CncImgLoadVPLFile(const unsigned char* pBuffer);
	__declspec(dllimport) bool __stdcall CncImgLoadVXLFile(const unsigned char* pBuffer);
	__declspec(dllimport) bool __stdcall CncImgLoadHVAFile(const unsigned char* pBuffer);

	__declspec(dllimport) bool __stdcall CncImgPrepareVXLCache(unsigned int nFacing, int F, int L, int H);
	__declspec(dllimport) int __stdcall CncImgGetImageWidth(unsigned int nFacing);
	__declspec(dllimport) int __stdcall CncImgGetImageHeight(unsigned int nFacing);
	__declspec(dllimport) void __stdcall CncImgGetImageFrame(unsigned int nFacing, int* width, int* height, int* x, int* y);
	__declspec(dllimport) void __stdcall CncImgGetImageSize(unsigned int nFacing, int* width, int* height);
	__declspec(dllimport) bool __stdcall CncImgGetImageData(unsigned int nFacing, unsigned char** ppBuffer);

	__declspec(dllimport) void __stdcall CncImgClearCurrentVXL();
	__declspec(dllimport) bool __stdcall CncImgIsVXLLoaded();
	__declspec(dllimport) bool __stdcall CncImgIsVPLLoaded();
}
