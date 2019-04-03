//
// Created by nathan on 18.03.2019.
//

#ifndef MCS_4_EMULATOR_DEBUGGER_H
#define MCS_4_EMULATOR_DEBUGGER_H

#include "../core/Chipset.h"

class Chipset;

class Debugger {
private:
    Chipset *chipset;

    std::vector<mcs4::uint12_t> breakpoints;

    /**
     * Returns the index of the first breakpoint at the provided address, if any. Returns -1 if no breakpoints are set
     * there.
     *
     * @param addr
     * @return
     */
    long getBreakpointIndex(mcs4::uint12_t addr);

public:
    Debugger();

    void setChipset(Chipset *pChipset);

    void cpuInspector(const SysInfo *info);

    unsigned long setBreakpoint(mcs4::uint12_t addr);

    void removeBreakpoint(unsigned long index);
};


#endif //MCS_4_EMULATOR_DEBUGGER_H
