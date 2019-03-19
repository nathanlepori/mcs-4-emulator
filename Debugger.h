//
// Created by nathan on 18.03.2019.
//

#ifndef MCS_4_EMULATOR_DEBUGGER_H
#define MCS_4_EMULATOR_DEBUGGER_H


#include "Chipset.h"

class Chipset;

class Debugger {
private:
    Chipset *chipset;
public:
    Debugger();

    void setChipset(Chipset *chipset);

    void cpuInspector(const CpuInfo *info);
};


#endif //MCS_4_EMULATOR_DEBUGGER_H
