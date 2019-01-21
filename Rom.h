//
// Created by nathan on 20.12.2018.
//

#ifndef MCS_4_EMULATOR_ROM_H
#define MCS_4_EMULATOR_ROM_H

#include <cstddef>
#include <stdint.h>
#include "mcs4_stdint.h"

class Rom {
public:
    static const size_t ROM_SZ = 4096;    // In bytes

    Rom();

    explicit Rom(uint8_t *prog);

    uint8_t read(uint16_t addr);
private:
    uint8_t m[ROM_SZ];  // Rom content
    mcs4::uint4_t io;   // IO ports
};


#endif //MCS_4_EMULATOR_ROM_H
