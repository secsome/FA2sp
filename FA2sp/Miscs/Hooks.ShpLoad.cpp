#include <CMixFile.h>
#include <CShpFile.h>
#include <CLoading.h>
#include <FAMemory.h>
#include <CFinalSunApp.h>

#include <fstream>

#include <Helpers/Macro.h>
#include "../RunTime.h"

namespace hooks_files_detail
{
	struct shape_file
	{
		bool is_open() const
		{
			return m_data != nullptr;
		}

		void close()
		{
			if (m_data)
			{
				GameDelete(m_data);
				m_data = nullptr;
			}
		}
		
		template <typename T>
		T& at(size_t offset) const
		{
			return *const_cast<T*>(reinterpret_cast<const T*>(m_data + offset));
		}

		unsigned char* m_data;
	};
	static shape_file current_shape_file;
}
using namespace hooks_files_detail;

DEFINE_HOOK(525C50, CMixFile_LoadSHP, 5)
{
    GET_STACK(const char*, filename, 0x4);
    GET_STACK(int, nMix, 0x8);

    if (current_shape_file.is_open())
		current_shape_file.close();

	ppmfc::CString filepath = CFinalSunApp::FilePath();
	filepath += filename;
	std::ifstream fin;
	fin.open(filepath, std::ios::in | std::ios::binary);
	if (fin.is_open())
	{
		fin.seekg(0, std::ios::end);
		const int size = static_cast<int>(fin.tellg());
		if (size == 0)
			return false;

		fin.seekg(0, std::ios::beg);
		current_shape_file.m_data = GameCreateArray<unsigned char>(size);
		fin.read((char*)current_shape_file.m_data, size);
		fin.close();
		R->EAX(true);
	}
	else if (CMixFile::HasFile(filename, nMix))
	{
		Ccc_file file(true);
		file.open(filename, CMixFile::Array[nMix - 1]);
		current_shape_file.m_data = GameCreateArray<unsigned char>(file.get_size());
		memcpy(current_shape_file.m_data, file.get_data(), file.get_size());
		R->EAX(true);
	}
	else
		R->EAX(false);

    return 0x525CFC;
}

DEFINE_HOOK(525A30, CSHPFile_GetHeader, 6)
{
	GET_STACK(ShapeHeader*, pHeader, 0x4);

	if (pHeader && current_shape_file.is_open())
	{
		*pHeader = current_shape_file.at<ShapeHeader>(0);
		R->EAX(true);
	}
	else
	{
		R->EAX(false);
	}

	return 0x525A5B;
}

DEFINE_HOOK(525A60, CSHPFile_GetImageHeader, 7)
{
	GET_STACK(int, nFrame, 0x4);
	GET_STACK(ShapeImageHeader*, pImageHeader, 0x8);

	if (pImageHeader && nFrame >= 0 && current_shape_file.is_open() && nFrame < current_shape_file.at<short>(0x6))
	{
		*pImageHeader = current_shape_file.at<ShapeImageHeader>(nFrame * sizeof(ShapeImageHeader) + sizeof(ShapeHeader));
		R->EAX(true);
	}
	else
	{
		R->EAX(false);
	}

	return 0x525ACB;
}

DEFINE_HOOK(537129, ExeRun_CSHPFileBufferReplace, 9)
{
#pragma pack(push, 1)
	struct SHPHelperStruct
	{
		unsigned char Op;
		unsigned char** Address;
	};
#pragma pack(pop)
	static_assert(sizeof(SHPHelperStruct) == 5);

	SHPHelperStruct data;
	data.Op = 0xA1;
	data.Address = &current_shape_file.m_data;

	RunTime::ResetMemoryContentAt(0x526023, data);
	RunTime::ResetMemoryContentAt(0x5260B9, data);
	RunTime::ResetMemoryContentAt(0x52617F, data);
	RunTime::ResetMemoryContentAt(0x52619D, data);

	return 0;
}