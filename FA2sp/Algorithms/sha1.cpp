#include "sha1.h"

#include "sha1impl.h"
#include "sha1x86.h"

#include "../Helpers/InstructionSet.h"

void SHA1::hash(unsigned char buffer[20], const void* source, size_t length)
{
    // if (InstructionSet::SHA())
    // {
    //     auto state = reinterpret_cast<uint32_t*>(buffer);
    //     state[0] = 0x67452301;
    //     state[1] = 0xefcdab89;
    //     state[2] = 0x98badcfe;
    //     state[3] = 0x10325476;
    //     state[4] = 0xc3d2e1f0;
    //     sha1x86::sha1_compress(state, reinterpret_cast<const uint8_t*>(source), length);
    // }
    // else
    {
        SHA1Impl engine;
        engine.add(source, length);
        engine.getHash(buffer);
    }
}
