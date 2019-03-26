//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_CPU_H
#define MCS_4_EMULATOR_CPU_H

#include <cstddef>
#include <stdint.h>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <boost/signals2.hpp>

#include "Rom.h"
#include "Ram.h"
#include "../InstructionSet.h"
#include "../../mcs4_stdint.h"
#include "../../SysInfo.h"

class InstructionSet;

/**
 * Holds an instruction as function pointer (after the fetch phase). Instructions are differentiated only by the first
 * four bits (different instructions having the same four bits are handled in wrapper functions) and are at most 2 bytes
 * long (for 2-word instructions). Hence the argument is 12-bits long.
 */
typedef void (InstructionSet::*instr_p)(mcs4::uint12_t);

class Cpu {
private:
    static const size_t REG_NUM = 16;
    static const size_t STACK_SZ = 3;
    static const unsigned int CLOCK_SPEED = 750000;

    // These two variables are grouped together to save memory
    mcs4::uint5_t acc_cy;                  // Accumulator + carry
    uint8_t r[REG_NUM / 2];            // Registers: 16 x 4bit

    uint8_t data_ptr;
    mcs4::uint12_t code_ptr;   // Aka instruction pointer

    mcs4::uint12_t stack[STACK_SZ];                  // Each "cell" is 12 bit wide
    uint8_t stack_ptr;

    InstructionSet *const i_set;

    // Signal is sent to the outside world (i.e. debugger) when a CPU cycle starts
    boost::signals2::signal<void(SysInfo *)> cycle_sig;

    uint8_t readInstruction();

    uint8_t readSecondInstruction();

    void fetch(instr_p &instr, mcs4::uint12_t &modifier);

    void execute(instr_p instr, mcs4::uint12_t modifier);

    void waitClockTime(std::chrono::duration<double> exec_time);

    void runCycle();

    void getCurrentSysInfo(SysInfo *);

public:
    // Other peripherals
    Rom *const rom;
    Ram *const ram;

    Cpu(Rom *const rom, Ram *const ram);

    virtual ~Cpu();

    // Accumulator and carry

    mcs4::uint4_t readAccumulator();

    void writeAccumulator(mcs4::uint4_t value);

    mcs4::uint1_t readCarry();

    void writeCarry(mcs4::uint1_t value);

    void writeAccumulatorAndCarry(mcs4::uint5_t value);

    // Index registers R/W

    mcs4::uint4_t readRegister(mcs4::uint4_t index);    // Index is at most 15 (0b1111)
    void writeRegister(mcs4::uint4_t index, mcs4::uint4_t value);

    uint8_t readDataPtr();

    void writeDataPtr(uint8_t value);

    mcs4::uint12_t readCodePtr();

    void writeCodePtr(mcs4::uint12_t addr);

    void incrementCodePtr();

    void pushStack();

    mcs4::uint12_t popStack();

    void run();

    void attachInspector(std::function<void(const SysInfo *)> &);
};


#endif //MCS_4_EMULATOR_CPU_H
