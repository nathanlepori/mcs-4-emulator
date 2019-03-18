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

auto insp = [](CpuInfo *info) -> void {
    std::cout << "From inspector: code_ptr=0x" << std::hex << info->code_ptr << std::endl;
};

Chipset::Chipset(const uint8_t *prog, const uint8_t numRoms) :
        ram(new Ram()),
        rom(new Rom(prog, numRoms)),
        cpu(new Cpu(rom, ram))  {
    /*---------- Debug ----------*/
    this->cpu->attachInspector(insp);
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
