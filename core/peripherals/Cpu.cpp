//
// Created by nathan on 19.12.2018.
//

#include <cstring>
#include <thread>
#include <iostream>

#include "Cpu.h"
#include "../../common/util.h"
#include "Rom.h"
#include "Ram.h"
#include "../../debugger/SysInfo.h"

Cpu::Cpu(Rom *const rom, Ram *const ram) :
        rom(rom),
        ram(ram),
        acc_cy(0),
        r{0},
        data_ptr(0),
        code_ptr(0),
        stack{0},
        stack_ptr(0),
        i_set(new InstructionSet(this)) {}

Cpu::~Cpu() {
    delete this->i_set;
}

uint8_t Cpu::readRegister(const uint8_t index) {
    // Registers are only 4 bit wide
    if (index % 2 == 0) {
        return l4b(this->r[index / 2]);
    } else {
        return h4b(this->r[index / 2]);
    }
}

void Cpu::writeRegister(const uint8_t index, uint8_t value) {
    // Keep only the lower 4 bits
    value = l4b(value);

    if (index % 2 == 0) {
        // Clear and overwrite high 4 bits
        this->r[index / 2] &= 0xf;
        this->r[index / 2] |= value << 4;
    } else {
        // Clear and overwrite low 4 bits
        this->r[index / 2] &= 0xf0;
        this->r[index / 2] |= value;
    }
}

uint8_t Cpu::readAccumulator() {
    return l4b(this->acc_cy);
}

void Cpu::writeAccumulator(uint8_t value) {
    value = l4b(value);

    this->acc_cy &= 0x10;           // Clear the lower 4 bits
    this->acc_cy |= value;
}

uint8_t Cpu::readCarry() {
    return h1b(this->acc_cy);
}

void Cpu::writeCarry(uint8_t value) {
    value = l1b(value);

    this->acc_cy &= 0xf;    // Clear higher 1 bit
    this->acc_cy |= value << 4;
}

void Cpu::writeAccumulatorAndCarry(uint8_t value) {
    value = l5b(value);

    this->acc_cy = value;
}

uint8_t Cpu::readDataPtr() {
    return this->data_ptr;
}

void Cpu::writeDataPtr(uint8_t value) {
    this->data_ptr = value;
}

mcs4::uint12_t Cpu::readCodePtr() {
    return this->code_ptr;
}

void Cpu::writeCodePtr(mcs4::uint12_t addr) {
    this->code_ptr = addr;
}

uint8_t Cpu::readInstruction() {
    return this->rom->read(this->code_ptr);
}

uint8_t Cpu::readSecondInstruction() {
    return this->rom->read(this->code_ptr + (uint16_t) 1);
}

void Cpu::fetch(instr_p &instr, mcs4::uint12_t &modifier) {
    uint8_t bin_instr = this->readInstruction();

    instr = this->i_set->fetchOpcode(bin_instr);

    if (this->i_set->is2WordInstruction(bin_instr)) {
        // Assemble the 12 bit modifier
        uint8_t m0 = l4b(bin_instr);
        uint8_t m1 = this->readSecondInstruction();

        modifier = (m0 << 8) | m1;
    } else {
        modifier = l4b(bin_instr);
    }
}

void Cpu::execute(instr_p instr, mcs4::uint12_t modifier) {
    (this->i_set->*instr)(modifier);
}

void Cpu::incrementCodePtr() {
    if (this->i_set->is2WordInstruction(this->readInstruction())) {
        code_ptr += 2;
    } else {
        code_ptr++;
    }
}

void Cpu::waitClockTime(std::chrono::duration<double> exec_time) {
    std::chrono::duration<double> clock_time = std::chrono::duration<double>((double) 1 / Cpu::CLOCK_SPEED);
    std::this_thread::sleep_for(clock_time - exec_time);
}

void Cpu::runCycle() {
    using namespace std::chrono;

    high_resolution_clock::time_point t0 = high_resolution_clock::now();

    instr_p instr;
    uint16_t modifier;

    this->fetch(instr, modifier);

    // Check if it's a jump instruction before doing anything, as it may modify the code pointer, pointing to a
    // different instruction
    bool is_jump = this->i_set->isJumpInstruction(this->readInstruction());

    // Execute the instruction
    this->execute(instr, modifier);

    // Increment the code pointer if the executed instruction is anything but a jump instruction (in which case the
    // code ptr is already in the right location)
    if (!is_jump) {
        this->incrementCodePtr();
    }

    // Handle cycle waiting (real CPU is slower than emulated one)
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    duration<double> t = duration_cast<duration<double>>(t1 - t0);

    this->waitClockTime(t);
}

void Cpu::pushStack() {
    mcs4::uint12_t addr;

    // The only instruction to push the stack afaik is JMS (which is a 2-word instruction). But for the sake of
    // completeness the check is included.
    if (this->i_set->is2WordInstruction(this->readInstruction())) {
        addr = this->code_ptr + (mcs4::uint12_t) 2;
    } else {
        addr = this->code_ptr + (mcs4::uint12_t) 1;
    }

    if (stack_ptr >= Cpu::STACK_SZ) {
        std::cerr << "Cannot push more than 3 addresses onto the stack" << std::endl;
        return;
    }

    this->stack[this->stack_ptr++] = addr;
}

mcs4::uint12_t Cpu::popStack() {
    return this->stack[--this->stack_ptr];
}

void Cpu::run() {
    while (this->code_ptr < this->rom->romSz) {
        SysInfo info;
        this->getCurrentSysInfo(&info);

        // Call inspector callback method such as debugger, ...
        this->cycle_sig(&info);

        this->runCycle();
    }
}

void Cpu::attachInspector(std::function<void(const SysInfo *)> &inspector) {
    this->cycle_sig.connect(inspector);
}

void Cpu::getCurrentSysInfo(SysInfo *info) {
    info->acc = this->readAccumulator();
    info->cy = this->readCarry();

    for (mcs4::uint4_t i = 0; i < Cpu::REG_NUM; ++i) {
        info->r[i] = readRegister(i);
    }


    info->data_ptr = this->data_ptr;
    info->code_ptr = this->code_ptr;

    std::copy(this->stack, this->stack + Cpu::STACK_SZ, info->stack);

    info->stack_ptr = this->stack_ptr;

    // Prepare raw instruction info
    uint16_t current_instr = this->readInstruction();
    if (this->i_set->is2WordInstruction((uint8_t) current_instr)) {
        current_instr = (this->readSecondInstruction() << 8) | current_instr;
    }
    info->raw_instr = current_instr;

    // Prepare ROM I/O info
    mcs4::uint4_t rom_io[ROM_MAX_IO] = {0};
    for (mcs4::uint4_t b = 0; b < this->rom->numRoms; ++b) {
        rom_io[b] = this->rom->readPort(b);
    }
    std::copy(rom_io, rom_io + ROM_MAX_IO, info->rom_io);
}
