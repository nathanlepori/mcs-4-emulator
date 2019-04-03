//
// Created by nathan on 18.03.2019.
//

#include <iostream>

#include "Debugger.h"
#include "../common/util.h"

Debugger::Debugger(): chipset(nullptr) {}

void Debugger::cpuInspector(const SysInfo *info) {
    long bIndex = this->getBreakpointIndex(info->code_ptr);
    if (bIndex != -1) {
        std::cout << "Stopped by debugger at breakpoint " << bIndex << ". Code ptr.: $" << std::hex << info->code_ptr << std::endl;
        std::cin.get();
    }
}

void Debugger::setChipset(Chipset *pChipset) {
    this->chipset = pChipset;
}

long Debugger::getBreakpointIndex(mcs4::uint12_t addr) {
    auto it = std::find(this->breakpoints.begin(), this->breakpoints.end(), addr);
    if (it != this->breakpoints.end()) {
        return std::distance(this->breakpoints.begin(), it);
    }
    return -1;
}

unsigned long Debugger::setBreakpoint(mcs4::uint12_t addr) {
    this->breakpoints.push_back(addr);
    return this->breakpoints.size() - 1;
}

void Debugger::removeBreakpoint(unsigned long index) {
    this->breakpoints.erase(this->breakpoints.begin() + index);
}
