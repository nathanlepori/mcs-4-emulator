//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_CHIPSET_H
#define MCS_4_EMULATOR_CHIPSET_H


#include "Ram.h"
#include "Cpu.h"
#include "Rom.h"

class Chipset {
private:
    Rom * const rom;
    Ram * const ram;
    Cpu * const cpu;
public:
    Chipset();

    explicit Chipset(uint8_t prog[]);

    void powerOn();
};


#endif //MCS_4_EMULATOR_CHIPSET_H
