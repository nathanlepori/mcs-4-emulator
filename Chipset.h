//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_CHIPSET_H
#define MCS_4_EMULATOR_CHIPSET_H

#include <thread>

#include "Ram.h"
#include "Cpu.h"
#include "Rom.h"
#include "Debugger.h"

class Debugger;

class Chipset {
private:
    Rom *const rom;
    Ram *const ram;
    Cpu *const cpu;
public:
    explicit Chipset(const uint8_t prog[]);

    Chipset(const uint8_t prog[], uint8_t numRoms);

    virtual ~Chipset();

    std::thread powerOn();

    void pauseCpu();
    void signalCpu();

    void attachDebugger(Debugger *const debugger);
};


#endif //MCS_4_EMULATOR_CHIPSET_H
