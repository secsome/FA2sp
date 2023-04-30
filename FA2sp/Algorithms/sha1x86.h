#pragma once

#include <vector>
#include <cstdint>

class sha1x86
{
public:
    // static void sha1_compress(uint32_t state[5], const uint8_t input[], size_t length);
    static void sha1_compress_x86(uint32_t state[5], const uint8_t input[], size_t blocks);
};