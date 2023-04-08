#include "Body.h"

#include <Helpers/Macro.h>

#include "../../FA2sp.h"

#include <CFinalSunDlg.h>

DEFINE_HOOK(4B5460, CMapData_InitializeBuildingTypes, 7)
{
	GET(CMapDataExt*, pThis, ECX);
	GET_STACK(const char*, ID, 0x4);

	auto ProcessType = [pThis](const char* ID)
	{
		int idx = pThis->GetBuildingTypeID(ID);
		auto& DataExt = pThis->BuildingDataExts[idx];
		ppmfc::CString ImageID = ID;
		if (ppmfc::CString* pArtID = Variables::Rules.TryGetString(ID, "Image"))
			ImageID = *pArtID;

		auto foundation = CINI::Art->GetString(ImageID, "Foundation");
		if (_strcmpi(foundation, "Custom"))
		{
			DataExt.Width = atoi(foundation);
			DataExt.Height = atoi(&foundation[2]);
			if (DataExt.Width == 0)
				DataExt.Width = 1;
			if (DataExt.Height == 0)
				DataExt.Height = 1;
		}
		else
		{
			// Custom, code reference Ares
			DataExt.Width = CINI::Art->GetInteger(ImageID, "Foundation.X", 0);
			DataExt.Height = CINI::Art->GetInteger(ImageID, "Foundation.Y", 0);
			DataExt.Foundations = new std::vector<MapCoord>;
			auto ParsePoint = [](const char* str)
			{
				int x = 0, y = 0;
				switch (sscanf_s(str, "%d,%d", &x, &y)) 
				{
				case 0:
					x = 0;
					y = 0;
					break;
				case 1:
					y = 0;
					break;
				case 2:
					break;
				default:
					__assume(0);
				}
				return MapCoord{ x,y };
			};
			for (int i = 0; i < DataExt.Width * DataExt.Height; ++i) 
			{
				ppmfc::CString key;
				key.Format("Foundation.%d", i);
				if (auto ppPoint = CINI::Art->TryGetString(ImageID, key))
					DataExt.Foundations->push_back(ParsePoint(*ppPoint));
				else
					break;
			}

			// Build outline draw data
			DataExt.LinesToDraw = new std::vector<std::pair<MapCoord, MapCoord>>;
			std::vector<std::vector<BOOL>> LinesX, LinesY; 
			
			LinesX.resize(DataExt.Width);
			for (auto& l : LinesX)
				l.resize(DataExt.Height + 1);
			LinesY.resize(DataExt.Width + 1);
			for (auto& l : LinesY)
				l.resize(DataExt.Height);

			for (const auto& block : *DataExt.Foundations)
			{
				LinesX[block.X][block.Y] = !LinesX[block.X][block.Y];
				LinesX[block.X][block.Y + 1] = !LinesX[block.X][block.Y + 1];
				LinesY[block.X][block.Y] = !LinesY[block.X][block.Y];
				LinesY[block.X + 1][block.Y] = !LinesY[block.X + 1][block.Y];
			}

			for (size_t y = 0; y < DataExt.Height + 1; ++y)
			{
				size_t length = 0;
				for (size_t x = 0; x < DataExt.Width; ++x)
				{
					if (LinesX[x][y])
						++length;
					else
					{
						if (!length)
							continue;
						MapCoord start, end;
						start.X = ((x - length) - y) * 30;
						start.Y = ((x - length) + y) * 15;
						end.X = (x - y) * 30;
						end.Y = (x + y) * 15;
						DataExt.LinesToDraw->push_back(std::make_pair(start, end));
						length = 0;
					}
				}
				if (length)
				{
					MapCoord start, end;
					start.X = ((DataExt.Width - length) - y) * 30;
					start.Y = ((DataExt.Width - length) + y) * 15;
					end.X = (DataExt.Width - y) * 30;
					end.Y = (DataExt.Width + y) * 15;
					DataExt.LinesToDraw->push_back(std::make_pair(start, end));
				}
			}

			for (size_t x = 0; x < DataExt.Width + 1; ++x)
			{
				size_t length = 0;
				for (size_t y = 0; y < DataExt.Height; ++y)
				{
					if (LinesY[x][y])
						++length;
					else
					{
						if (!length)
							continue;
						MapCoord start, end;
						start.X = (x - (y - length)) * 30;
						start.Y = (x + (y - length)) * 15;
						end.X = (x - y) * 30;
						end.Y = (x + y) * 15;
						DataExt.LinesToDraw->push_back(std::make_pair(start, end));
						length = 0;
					}
				}
				if (length)
				{
					MapCoord start, end;
					start.X = (x - (DataExt.Height - length)) * 30;
					start.Y = (x + (DataExt.Height - length)) * 15;
					end.X = (x - DataExt.Height) * 30;
					end.Y = (x + DataExt.Height) * 15;
					DataExt.LinesToDraw->push_back(std::make_pair(start, end));
				}
			}
		}
	};

	pThis->UpdateTypeDatas();
	if (ID)
		ProcessType(ID);
	else
	{
		pThis->BuildingDataExts.clear();
		const auto Types = Variables::Rules.GetSection("BuildingTypes");
		for (auto& Type : Types)
			ProcessType(Type.second);
	}

	return 0;
}

DEFINE_HOOK(4A5089, CMapData_UpdateMapFieldData_Structures_CustomFoundation, 6)
{
	GET(int, BuildingIndex, ESI);
	GET_STACK(const int, X, STACK_OFFS(0x16C, 0x104));
	GET_STACK(const int, Y, STACK_OFFS(0x16C, 0x94));

	const auto& DataExt = CMapDataExt::BuildingDataExts[BuildingIndex];
	if (!DataExt.IsCustomFoundation())
	{
		for (int dy = 0; dy < DataExt.Width; ++dy)
		{
			for (int dx = 0; dx < DataExt.Height; ++dx)
			{
				const int x = X + dx;
				const int y = Y + dy;
				auto pCell = CMapData::Instance->GetCellAt(x, y);
				pCell->Structure = R->BX();
				pCell->TypeListIndex = BuildingIndex;
				CMapData::Instance->UpdateMapPreviewAt(x, y);
			}
		}
	}
	else
	{
		for (const auto& block : *DataExt.Foundations)
		{
			const int x = X + block.Y;
			const int y = Y + block.X;
			auto pCell = CMapData::Instance->GetCellAt(x, y);
			pCell->Structure = R->BX();
			pCell->TypeListIndex = BuildingIndex;
			CMapData::Instance->UpdateMapPreviewAt(x, y);
		}
	}

	return 0x4A57CD;
}