//
// Created by nathan on 18.03.2019.
//

#ifndef MCS_4_EMULATOR_DEBUGGER_H
#define MCS_4_EMULATOR_DEBUGGER_H


#include "core/Chipset.h"

class Chipset;

typedef std::pair<std::string, std::string> instr_info;

class Debugger {
private:
    Chipset *chipset;

public:
    Debugger();

    void setChipset(Chipset *chipset);

    void cpuInspector(const SysInfo *info);

};


#endif //MCS_4_EMULATOR_DEBUGGER_H
