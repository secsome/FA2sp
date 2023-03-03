#pragma once

#include <Helpers/Macro.h>
#include "Logger.h"

class RunTime
{
public:
	struct Messages
	{
		static auto constexpr EDIT_KILLFOCUS = EN_KILLFOCUS;
		static auto constexpr COMBOBOX_KILLFOCUS = CBN_KILLFOCUS;
	};
	

	using ptr_type = unsigned long;
	static void ResetMemoryContentAt(ptr_type addr, const void* content, size_t size, size_t offset = 0);
	
	template<typename T>
	static inline void ResetMemoryContentAt(DWORD addr, T value)
	{
		RunTime::ResetMemoryContentAt(addr, &value, sizeof(T));
	}

	static void SetJump(DWORD from, DWORD to);

	RunTime();
	~RunTime();

};