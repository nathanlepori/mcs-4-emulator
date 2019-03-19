//
// Created by nathan on 19.12.2018.
//

#include <iostream>
#include "Chipset.h"

Chipset::Chipset(const uint8_t *prog) :
        ram(new Ram()),
        rom(new Rom(prog, 16)),
        cpu(new Cpu(rom, ram)) {
}

Chipset::Chipset(const uint8_t *prog, const uint8_t numRoms) :
        ram(new Ram()),
        rom(new Rom(prog, numRoms)),
        cpu(new Cpu(rom, ram)) {
}

Chipset::~Chipset() {
    delete this->rom;
    delete this->ram;
    delete this->cpu;
}

std::thread Chipset::powerOn() {
    // Start CPU thread and return pointer to thread
    std::thread cpu_thread(&Cpu::run, this->cpu);

    return cpu_thread;
}

void Chipset::pauseCpu() {
    this->cpu->pause();
}

void Chipset::signalCpu() {
    this->cpu->signal();
}

void Chipset::attachDebugger(Debugger *const debugger) {
    debugger->setChipset(this);

    // Wrap in a lambda to pass member function as argument
    std::function<void(const CpuInfo *)> insp = [&debugger](const CpuInfo *info) { debugger->cpuInspector(info); };
    this->cpu->attachInspector(insp);
}
