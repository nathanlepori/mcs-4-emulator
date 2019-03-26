//
// Created by nathan on 12.03.2019.
//

#ifndef MCS_4_EMULATOR_CPUINFO_H
#define MCS_4_EMULATOR_CPUINFO_H

#include "core/peripherals/Cpu.h"

typedef struct {
    // Processor registers and stack
    mcs4::uint4_t acc;
    mcs4::uint1_t cy;
    mcs4::uint4_t r[16];    // Registers expanded to 16 variables instead of 8 groups of 2 for better handling by the debugger
                            // TODO: Find a way to put in a const

    uint8_t data_ptr;
    mcs4::uint12_t code_ptr;

    mcs4::uint12_t stack[3];
    uint8_t stack_ptr;

    // Processor info
    uint16_t raw_instr;
} CpuInfo;

#endif //MCS_4_EMULATOR_CPUINFO_H
