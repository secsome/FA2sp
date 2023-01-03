#include "Body.h"

#include <Helpers/Macro.h>

#include "../../Logger.h"

#include "../../Algorithms/base64.h"
#include "../../Algorithms/lcw.h"
#include "../../Algorithms/lzo.h"

void CMapDataExt::PackExt(bool UpdatePreview, bool Description)
{
	UNREFERENCED_PARAMETER(Description);

	if (FieldDataAllocated)
	{
		Logger::Raw(
			"CMapDataExt::PackExt called!\n"
			"UpdatePreview = %d, Description = %d\n"
			"Erasing sections\n",
			UpdatePreview, Description
		);

		INI.DeleteSection("OverlayPack");
		INI.DeleteSection("OverlayDataPack");
		INI.DeleteSection("IsoMapPack5");
		INI.DeleteSection("Digest");

		{
			Logger::Raw("Packing overlay\n");
			auto data = lcw::compress(Overlay, 0x40000);
			data = base64::encode(data);
			Logger::Raw("Saving overlay...");
			INI.WriteBase64String("OverlayPack", data.data(), data.length());
			Logger::Raw(" done\n");
		}

		{
			Logger::Raw("Packing overlaydata\n");
			auto data = lcw::compress(OverlayData, 0x40000);
			data = base64::encode(data);
			Logger::Raw("Saving overlaydata...");
			INI.WriteBase64String("OverlayDataPack", data.data(), data.length());
			Logger::Raw(" done\n");
		}

		{
			Logger::Raw("Packing isomappack\n");
			auto data = lzo::compress(IsoPackData, IsoPackDataCount * sizeof(IsoMapPack5Entry));
			data = base64::encode(data);
			Logger::Raw("Saving isomappack...");
			INI.WriteBase64String("IsoMapPack5", data.data(), data.length());
			Logger::Raw(" done\n");
		}

		if (UpdatePreview)
		{
			Logger::Raw("Packing previewpack\n");
			
			BITMAPINFO info; void* buffer; int stride;
			GetMapPreview(buffer, &info, stride);

			const int width = info.bmiHeader.biWidth;
			const int height = info.bmiHeader.biHeight;
			auto rawdata = new unsigned char[3 * width * height];
			const unsigned char* p = (const unsigned char*)buffer;
			for (int x = 0; x < width; ++x)
			{
				for (int y = 0; y < height; ++y)
				{
					const int idx = 3 * (x + width * y);
					auto clr = p + stride * (height - y - 1);
					// RGB <- BGR
					rawdata[idx + 0] = clr[2];
					rawdata[idx + 1] = clr[1];
					rawdata[idx + 2] = clr[0];
				}
				p += 3;
			}
			auto data = lzo::compress(rawdata, 3 * width * height);
			delete[] rawdata;
			data = base64::encode(data);
			Logger::Raw("Saving previewpack...");
			INI.WriteBase64String("PreviewPack", data.data(), data.length());
			
			ppmfc::CString size;
			size.Format("0,0,%d,%d", width, height);
			INI.WriteString("PreviewPack", "Size", size);
			Logger::Raw(" done\n");
		}
	}
}

DEFINE_HOOK(49F7A0, CMapData_Pack, 7)
{
	GET(CMapDataExt*, pThis, ECX);
	GET_STACK(bool, UpdatePreview, 0x4);
	GET_STACK(bool, Description, 0x4);

	pThis->PackExt(UpdatePreview, Description);

	return 0x4A1674;
}