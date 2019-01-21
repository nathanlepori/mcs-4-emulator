//
// Created by nathan on 19.12.2018.
//

#include "Chipset.h"

Chipset::Chipset() :
        ram(new Ram()),
        rom(new Rom()),
        cpu(new Cpu(rom, ram)) {
}

Chipset::Chipset(uint8_t *prog) :
        ram(new Ram()),
        rom(new Rom(prog)),
        cpu(new Cpu(rom, ram)) {
}

void Chipset::powerOn() {
    this->cpu->run();
}
