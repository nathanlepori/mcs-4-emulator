//
// Created by nathan on 20.12.2018.
//

#ifndef MCS_4_EMULATOR_ROM_H
#define MCS_4_EMULATOR_ROM_H

#include <cstddef>
#include <cstdint>
#include "../../mcs4_stdint.h"

class Rom {
public:
    static const size_t CHIP_SZ = 256;  // In bytes
    static const size_t MAX_CHIPS = 16;
    static const size_t MAX_ROM_SZ = CHIP_SZ * MAX_CHIPS;    // In bytes

    const size_t romSz;
    const uint8_t numRoms;

    Rom(const uint8_t *prog, uint8_t numRoms);

    virtual ~Rom();

    uint8_t read(mcs4::uint12_t addr);

    mcs4::uint4_t readPort(mcs4::uint4_t bank);
    void writePort(mcs4::uint4_t bank, mcs4::uint4_t value);
private:
    uint8_t *m;         // Rom content
    uint8_t *io;   // IO ports
};


#endif //MCS_4_EMULATOR_ROM_H
