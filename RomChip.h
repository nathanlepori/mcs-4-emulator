//
// Created by nathan on 21.01.2019.
//

#ifndef MCS_4_EMULATOR_ROMCHIP_H
#define MCS_4_EMULATOR_ROMCHIP_H


#include <cstddef>
#include <cstdint>
#include "mcs4_stdint.h"

class RomChip {
public:
    static const size_t ROM_SZ = 256;    // In bytes

private:
    uint8_t m[ROM_SZ];  // Rom content
    mcs4::uint4_t io;   // IO ports
};


#endif //MCS_4_EMULATOR_ROMCHIP_H
