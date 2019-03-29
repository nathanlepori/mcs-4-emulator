//
// Created by nathan on 19.12.2018.
//

#include <iostream>
#include "Chipset.h"

Chipset::Chipset(const uint8_t *prog) :
        ram(new Ram(16)),
        rom(new Rom(prog, 16)),
        cpu(new Cpu(rom, ram)) {
}

Chipset::Chipset(const uint8_t *prog, const uint8_t numRoms, const uint8_t numRams) :
        ram(new Ram(numRams)),
        rom(new Rom(prog, numRoms)),
        cpu(new Cpu(rom, ram)) {
}

Chipset::~Chipset() {
    delete this->rom;
    delete this->ram;
    delete this->cpu;
}

void Chipset::powerOn() {
    this->cpu->run();
}

void Chipset::attachDebugger(Debugger *const debugger) {
    debugger->setChipset(this);

    // Wrap in a lambda to pass member function as argument
    std::function<void(const SysInfo *)> insp = [debugger](const SysInfo *info) { debugger->cpuInspector(info); };
    this->cpu->attachInspector(insp);
}
