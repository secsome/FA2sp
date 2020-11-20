#pragma once

#include "..\FA2sp.h"
#include "Parser.h"

#include <CINI.h>
#include <algorithm>

class INI_SP {
	INIClass* IniFile;

public:
	explicit INI_SP(INIClass* pIniFile)
		: IniFile(pIniFile)
	{ }

	char* value() const {
		return INI_SP::readBuffer;
	}

	size_t max_size() const {
		return INI_SP::readLength;
	}

	bool empty() const {
		return !INI_SP::readBuffer[0];
	}

	// basic string reader
	size_t ReadString(const char* pSection, const char* pKey) {
		auto& pValue = IniFile->GetString(pSection, pKey);
		auto const& ret = pValue.GetLength();
		auto const size = std::min(ret + 1, (int)this->max_size());
		memcpy_s(this->value(), size, pValue, size);
		return static_cast<size_t>(ret);
	}

	// parser template
	template <typename T, size_t Count>
	bool Read(const char* pSection, const char* pKey, T* pBuffer) {
		if (this->ReadString(pSection, pKey)) {
			return Parser<T, Count>::Parse(this->value(), pBuffer) == Count;
		}
		return false;
	}

	// helpers

	bool ReadBool(const char* pSection, const char* pKey, bool* bBuffer) {
		return Read<bool, 1>(pSection, pKey, bBuffer);
	}

	bool ReadInteger(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 1>(pSection, pKey, nBuffer);
	}

	bool Read2Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 2>(pSection, pKey, nBuffer);
	}

	bool Read3Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 3>(pSection, pKey, nBuffer);
	}

	bool Read4Integers(const char* pSection, const char* pKey, int* nBuffer) {
		return Read<int, 4>(pSection, pKey, nBuffer);
	}

	bool Read3Bytes(const char* pSection, const char* pKey, byte* nBuffer) {
		return Read<byte, 3>(pSection, pKey, nBuffer);
	}

	bool ReadDouble(const char* pSection, const char* pKey, double* nBuffer) {
		return Read<double, 1>(pSection, pKey, nBuffer);
	}


public:
	static const size_t readLength = 2048;
	static char readBuffer[readLength];

};
