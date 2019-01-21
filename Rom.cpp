//
// Created by nathan on 20.12.2018.
//

#include <cstring>
#include <algorithm>
#include "Rom.h"

Rom::Rom() : m{0} {
    // Debug
    uint8_t code[] = {
            0x20, 0xA2, 0xA0, 0x81, 0xB1, 0x40, 0x05
    };

    memcpy(this->m, code, 7);
}

Rom::Rom(uint8_t *prog) {
    memcpy(this->m, prog, Rom::ROM_SZ);
}

uint8_t Rom::read(uint16_t addr) {
    return this->m[addr];
}
