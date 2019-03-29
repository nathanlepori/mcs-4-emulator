//
// Created by nathan on 20.12.2018.
//

#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Rom.h"
#include "../../util.h"

Rom::Rom(const uint8_t *prog, const uint8_t numRoms) :
        numRoms(numRoms),
        romSz(numRoms * Rom::CHIP_SZ) {
    if (numRoms > Rom::MAX_CHIPS) {
        std::cerr << "ROM chips requested exceed the maximum number supported. Errors may occur." << std::endl;
    }

    this->m = new uint8_t[this->romSz];

    std::memcpy(this->m, prog, this->romSz);

    auto num_io = static_cast<size_t>(ceil((double) numRoms / 2));
    this->io = new uint8_t[num_io];
    std::memset(this->io, 0, num_io);
}

uint8_t Rom::read(uint16_t addr) {
    return this->m[addr];
}

mcs4::uint4_t Rom::readPort(mcs4::uint4_t bank) {
    // Keep only the lower 4 bits
    bank = l4b(bank);

    if (bank % 2 == 0) {
        return l4b(this->io[bank / 2]);
    } else {
        return h4b(this->io[bank / 2]);
    }
}

void Rom::writePort(mcs4::uint4_t bank, mcs4::uint4_t value) {
    // Keep only the lower 4 bits
    bank = l4b(bank);
    value = l4b(value);
    if (bank % 2 == 0) {
        // Clear and overwrite low 4 bits
        this->io[bank / 2] &= 0xf0;
        this->io[bank / 2] |= value;
    } else {
        // Clear and overwrite high 4 bits
        this->io[bank / 2] &= 0xf;
        this->io[bank / 2] |= value << 4;
    }
}

Rom::~Rom() {
    delete[] this->m;
    delete[] this->io;
}
