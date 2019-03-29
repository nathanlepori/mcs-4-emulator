//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_RAM_H
#define MCS_4_EMULATOR_RAM_H

#include <cstddef>
#include <cstdint>
#include "../../mcs4_stdint.h"

class Ram {
public:
    explicit Ram(uint8_t numRams);

    virtual ~Ram();

    mcs4::uint4_t read(uint8_t addr);
    void write(uint8_t addr, mcs4::uint4_t value);
private:
    static const size_t CHIP_SZ = 40;    // In bytes
    static const size_t MAX_CHIPS = 16;
    static const size_t MAX_RAM_SZ = CHIP_SZ * MAX_CHIPS;    // In bytes

    const size_t ramSz;
    const uint8_t numRams;

    uint8_t *m;    // Ram content
    uint8_t *io;   // IO ports
    // TODO: Implement status chars
};


#endif //MCS_4_EMULATOR_RAM_H
