//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_RAM_H
#define MCS_4_EMULATOR_RAM_H

#include <cstddef>
#include <stdint.h>

class Ram {
public:
    Ram();

    static const size_t RAM_SZ = 40;    // In bytes
private:
    // In bits
    uint8_t const m[RAM_SZ];    // Ram content
};


#endif //MCS_4_EMULATOR_RAM_H
