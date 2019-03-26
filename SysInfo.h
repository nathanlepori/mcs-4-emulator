//
// Created by nathan on 12.03.2019.
//

#ifndef MCS_4_EMULATOR_CPUINFO_H
#define MCS_4_EMULATOR_CPUINFO_H

#include "core/peripherals/Cpu.h"
#include "SysInfo.h"

#define CPU_REG_NUM 16
#define CPU_STACK_SZ 3
#define ROM_MAX_IO 16

/**
 * System snapshot passed to a CPU inspector.
 */
typedef struct {
    // Processor info
    // Processor registers and stack
    mcs4::uint4_t acc;
    mcs4::uint1_t cy;
    mcs4::uint4_t r[CPU_REG_NUM];    // Registers expanded to 16 variables instead of 8 groups of 2 for better handling by the debugger

    uint8_t data_ptr;
    mcs4::uint12_t code_ptr;

    mcs4::uint12_t stack[CPU_STACK_SZ];
    uint8_t stack_ptr;

    uint16_t raw_instr;

    // ROM info
    mcs4::uint4_t rom_io[ROM_MAX_IO];
} SysInfo;

#endif //MCS_4_EMULATOR_CPUINFO_H
