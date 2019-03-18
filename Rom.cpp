//
// Created by nathan on 20.12.2018.
//

#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Rom.h"
#include "util.h"

Rom::Rom(const uint8_t *prog, const uint8_t numRoms) :
        numRoms(numRoms),
        romSz(numRoms * Rom::ROM_CHIP_SZ) {
    if (numRoms > Rom::MAX_CHIPS) {
        std::cerr << "ROM chips requested exceed the maximum number supported. Errors may occur." << std::endl;
    }

    const size_t rom_sz = Rom::ROM_CHIP_SZ * numRoms;

    this->m = new uint8_t[rom_sz];

    memcpy(this->m, prog, rom_sz);

    auto num_io = static_cast<size_t>(ceil((double) numRoms / 2));
    this->io = new uint8_t[num_io];
    memset(this->io, 0, num_io);

    /*---------- Debug ----------*/
    this->writePort(0, 0xa);
    this->writePort(Rom::ROM_CHIP_SZ, 0x6);
    // Result 0x2
}

uint8_t Rom::read(uint16_t addr) {
    return this->m[addr];
}

mcs4::uint4_t Rom::readPort(uint16_t addr) {
    uint8_t index = this->addrToPort(addr);

    if (index % 2 == 0) {
        return l4b(this->io[index / 2]);
    } else {
        return h4b(this->io[index / 2]);
    }
}

void Rom::writePort(mcs4::uint12_t addr, mcs4::uint4_t value) {
    uint8_t index = this->addrToPort(addr);

    // Keep only the lower 4 bits
    value = l4b(value);
    if (index % 2 == 0) {
        // Clear and overwrite high 4 bits
        this->io[index / 2] &= 0xf;
        this->io[index / 2] |= value << 4;
    } else {
        // Clear and overwrite low 4 bits
        this->io[index / 2] &= 0xf0;
        this->io[index / 2] |= value;
    }
}

uint8_t Rom::addrToPort(uint16_t addr) {
    return static_cast<uint8_t>(floor((double) addr / Rom::ROM_CHIP_SZ));
}
