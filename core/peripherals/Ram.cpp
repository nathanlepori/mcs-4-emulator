//
// Created by nathan on 19.12.2018.
//

#include <cstring>
#include <iostream>
#include <cmath>
#include "Ram.h"
#include "../../util.h"

Ram::Ram(uint8_t numRams) :
        numRams(numRams),
        ramSz(numRams * Ram::CHIP_SZ) {
    if (numRams > Ram::MAX_CHIPS) {
        std::cerr << "RAM chips requested exceed the maximum number supported. Errors may occur." << std::endl;
    }

    this->m = new uint8_t[this->ramSz];
    std::memset(this->m, 0, this->ramSz);

    auto num_io = static_cast<size_t>(ceil((double) numRams / 2));
    this->io = new uint8_t[num_io];
    std::memset(this->io, 0, num_io);
}

Ram::~Ram() {
    delete[] this->m;
    delete[] this->io;
}

mcs4::uint4_t Ram::read(uint8_t addr) {
    if (addr % 2 == 0) {
        return l4b(this->m[addr / 2]);
    } else {
        return h4b(this->m[addr / 2]);
    }
}

void Ram::write(uint8_t addr, mcs4::uint4_t value) {
    // Keep only the lower 4 bits
    value = l4b(value);

    if (addr % 2 == 0) {
        // Clear and overwrite high 4 bits
        this->m[addr / 2] &= 0xf;
        this->m[addr / 2] |= value << 4;
    } else {
        // Clear and overwrite low 4 bits
        this->m[addr / 2] &= 0xf0;
        this->m[addr / 2] |= value;
    }
}
