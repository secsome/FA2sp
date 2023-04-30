#include "RunTime.h"

void RunTime::SetJump(DWORD from, DWORD to)
{
#pragma pack(push, 1)
	struct JumpStruct
	{
		JumpStruct(DWORD from, DWORD to)
			: OpCode{ 0xE9 }
			, Offset(to - from - 5)
		{}
		unsigned char OpCode;
		DWORD Offset;
	};
	static_assert(sizeof(JumpStruct) == 5);
#pragma pack(pop)
	JumpStruct data{ from,to };
	ResetMemoryContentAt(from, data);
}

RunTime::RunTime()
{
}


RunTime::~RunTime()
{
}

void RunTime::ResetMemoryContentAt(ptr_type addr, const void* content, size_t size, size_t offset)
{
	BYTE* pplContent = (BYTE*)(addr);
	auto process = GetCurrentProcess();
	DWORD oldProtect, newProtect = 0;
	auto ret = VirtualProtectEx(process, pplContent + offset, size, PAGE_READWRITE, &oldProtect);
	if (ret != TRUE) {
		Logger::Error("ResetMemoryContentAt , addr = %x, PAGE_READWRITE set failure, ret = %d", addr, ret);
	}
	memcpy(pplContent + offset, content, size);
	ret = VirtualProtectEx(process, pplContent + offset, size, oldProtect, &newProtect);
}