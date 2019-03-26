//
// Created by nathan on 18.03.2019.
//

#include <iostream>

#include "Debugger.h"
#include "util.h"

void Debugger::cpuInspector(const SysInfo *info) {

}

Debugger::Debugger() = default;

void Debugger::setChipset(Chipset *chipset) {
    Debugger::chipset = chipset;
}
