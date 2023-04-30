#pragma once

#include <cstdint>

class SHA1
{
public:
    static void hash(unsigned char buffer[20], const void* source, size_t length);
};