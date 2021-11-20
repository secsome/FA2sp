#include <CTileSetBrowserView.h>
#include <Helpers/Macro.h>

#include <FA2PP.h>

#include "../../FA2sp.h"

DEFINE_HOOK(4F258B, CTileSetBrowserView_OnDraw_SetOverlayFrameToDisplay, 7)
{
    GET(CTileSetBrowserView*, pThis, ESI);
    GET(const int, i, ECX);

    ppmfc::CString ovlIdx;
    ovlIdx.Format("%d", pThis->SelectedOverlayIndex);
    int nDisplayLimit = CINI::FAData->GetInteger("OverlayDisplayLimit", ovlIdx, 60);
    if (nDisplayLimit > 60)
        nDisplayLimit = 60;

    R->Stack(STACK_OFFS(0xDC, 0xB8), i);
    return i < nDisplayLimit ? 0x4F2230 : 0x4F2598;
}


//DEFINE_HOOK(4F1D70, ASDG, 6)
//{
//	Logger::Debug("%s %s %s %s %s %s\n", 
//        reinterpret_cast<const char*>(0x5D3358),
//        reinterpret_cast<const char*>(0x5D3354),
//        reinterpret_cast<const char*>(0x5D3350),
//        reinterpret_cast<const char*>(0x5D334C),
//        reinterpret_cast<const char*>(0x5D3348),
//        reinterpret_cast<const char*>(0x5D3344)
//        );
//	return 0;
//}

//
//DEFINE_HOOK(4F23CD, CTileSetBrowserView_CreateBMPPreview_DebugAsBmp, 6)
//{
//	GET(BITMAPINFO*, pBmi, EDX);
//	GET(char*, lpBits, EAX);
//
//	WORD* buffer = (WORD*)lpBits;
//	FILE* fp;
//	fopen_s(&fp, "bmpDebug.bmp", "wb");
//	if (fp)
//	{
//		int width = pBmi->bmiHeader.biWidth;
//		int height = pBmi->bmiHeader.biHeight;
//
//		size_t arrayLen = width * height;
//
//#pragma pack(push, 1)
//		struct bmpfile_full_header {
//			unsigned char magic[2];
//			DWORD filesz;
//			WORD creator1;
//			WORD creator2;
//			DWORD bmp_offset;
//			DWORD header_sz;
//			DWORD width;
//			DWORD height;
//			WORD nplanes;
//			WORD bitspp;
//			DWORD compress_type;
//			DWORD bmp_bytesz;
//			DWORD hres;
//			DWORD vres;
//			DWORD ncolors;
//			DWORD nimpcolors;
//			DWORD R; //
//			DWORD G; //
//			DWORD B; //
//		} h;
//#pragma pack(pop)
//		h.magic[0] = 'B';
//		h.magic[1] = 'M';
//		h.creator1 = h.creator2 = 0;
//		h.header_sz = 40;
//		h.width = width;
//		h.height = height;
//		h.nplanes = 1;
//		h.bitspp = 24;
//		h.compress_type = BI_BITFIELDS;
//		h.bmp_bytesz = arrayLen * 2;
//		h.hres = 4000;
//		h.vres = 4000;
//		h.ncolors = h.nimpcolors = 0;
//		h.R = 0xF800;
//		h.G = 0x07E0;
//		h.B = 0x001F;
//		h.bmp_offset = sizeof(h);
//		h.filesz = h.bmp_offset + h.bmp_bytesz;
//		fwrite(&h, 1, sizeof(h), fp);
//		std::unique_ptr<WORD[]> pixelData(new WORD[arrayLen * 2]);
//		WORD* pixels = pixelData.get();
//#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)
//		int pitch = WIDTHBYTES(width * 16);
//#undef WIDTHBYTES
//		for (int r = 0; r < height * 2; ++r) {
//			memcpy(pixels, reinterpret_cast<void*>(buffer), width * 2);
//			pixels += width;
//			buffer += pitch / 2; // /2 because buffer is a WORD * and pitch is in bytes
//		}
//		fwrite(pixelData.get(), 1, arrayLen * 4, fp);
//		fclose(fp);
//	}
//
//	return 0;
//}