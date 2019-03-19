//
// Created by nathan on 18.03.2019.
//

#include <iostream>

#include "Debugger.h"

void Debugger::cpuInspector(const CpuInfo *info) {
    std::cout << "Code ptr: " << std::hex << info->code_ptr << std::endl;
    std::cout << "Pausing CPU..." << std::endl;
    this->chipset->pauseCpu();
}

Debugger::Debugger() = default;

void Debugger::setChipset(Chipset *chipset) {
    Debugger::chipset = chipset;
}
