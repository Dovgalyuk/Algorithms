#ifndef MY_HASH_TEMPLATE_H
#define MY_HASH_TEMPLATE_H

#include <cstdint>
#include <string>

uint32_t my_hash(const std::string& key, uint32_t seed) {
    const int len = key.size();
    const uint8_t* data = reinterpret_cast<const uint8_t*>(key.data());
    const int nblocks = len / 4;

    uint32_t h1 = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    // Per 4 b
    const uint32_t* blocks = reinterpret_cast<const uint32_t*>(data);
    for (int i = 0; i < nblocks; ++i) {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15)); // ROTL32
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13)); // ROTL32
        h1 = h1 * 5 + 0xe6546b64;
    }

    // Other b
    const uint8_t* tail = data + nblocks * 4;
    uint32_t k1 = 0;

    switch (len & 3) { // len % 4
        case 3: k1 ^= tail[2] << 16; break;
        case 2: k1 ^= tail[1] << 8; break;
        case 1: k1 ^= tail[0];
                k1 *= c1;
                k1 = (k1 << 15) | (k1 >> (32 - 15)); // ROTL32
                k1 *= c2;
                h1 ^= k1;
                break;
    }

    // Final hash
    h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

#endif // MY_HASH_TEMPLATE_H