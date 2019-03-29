//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_CHIPSET_H
#define MCS_4_EMULATOR_CHIPSET_H

#include <thread>

#include "peripherals/Ram.h"
#include "peripherals/Cpu.h"
#include "peripherals/Rom.h"
#include "../Debugger.h"

class Debugger;

class Chipset {
private:
    Rom *const rom;
    Ram *const ram;
    Cpu *const cpu;
public:
    explicit Chipset(const uint8_t prog[]);

    Chipset(const uint8_t prog[], uint8_t numRoms, uint8_t numRams);

    virtual ~Chipset();

    void powerOn();

    void attachDebugger(Debugger *debugger);
};


#endif //MCS_4_EMULATOR_CHIPSET_H
