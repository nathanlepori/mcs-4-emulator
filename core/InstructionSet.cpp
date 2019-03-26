//
// Created by nathan on 19.12.2018.
//

#include <iostream>
#include <boost/algorithm/string.hpp>

#include "InstructionSet.h"
#include "peripherals/Cpu.h"
#include "../util.h"

InstructionSet::InstructionSet(Cpu *cpu) : cpu(cpu) {}

void InstructionSet::nop(mcs4::uint12_t) {}

// TODO: Test
void InstructionSet::jcn(mcs4::uint12_t m) {
    bool jump = false;

    mcs4::uint4_t c = h4b(m);     // Condition bits

    // TODO: Check if endianess is right
    mcs4::uint1_t c_invert = mask1bit(c, 3);
    mcs4::uint1_t c_acc_zero = mask1bit(c, 2);
    mcs4::uint1_t c_carry_one = mask1bit(c, 1);
    mcs4::uint1_t c_test_sig = mask1bit(c, 0);

    mcs4::uint4_t acc = cpu->readAccumulator();
    mcs4::uint1_t carry = cpu->readCarry();
    mcs4::uint1_t test_sig = 1;   // TODO: Unimplemented

    if (!c_invert) {
        if ((c_acc_zero && acc == 0) ||
            (c_carry_one && carry == 1) ||
            (c_test_sig && test_sig == 0)) {
            jump = true;
        }
    } else {
        if ((c_acc_zero && acc != 0) ||
            (c_carry_one && carry == 0) ||
            (c_test_sig && test_sig == 1)) {
            jump = true;
        }
    }

    if (jump) {
        // If condition is true, jump on the same page at this address
        mcs4::uint12_t addr = h4b(this->cpu->readCodePtr()) << 8 | l8b(m);

        this->cpu->writeCodePtr(addr);
    } else {
        this->cpu->incrementCodePtr();
    }
}

void InstructionSet::fim(mcs4::uint12_t m) {
    auto r0 = h4b(m);
    auto r1 = r0 + (mcs4::uint4_t) 1;

    auto d = l8b(m);
    mcs4::uint4_t d0 = h4b(d);
    mcs4::uint4_t d1 = l4b(d);

    this->cpu->writeRegister(r0, d0);
    this->cpu->writeRegister(r1, d1);
}

void InstructionSet::src(mcs4::uint12_t m) {
    mcs4::uint4_t r1 = l4b(m);
    mcs4::uint4_t r0 = r1 - (mcs4::uint4_t) 1;

    uint8_t v = (this->cpu->readRegister(r0) << 4) | this->cpu->readRegister(r1);
    this->cpu->writeDataPtr(v);
}

void InstructionSet::fin(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::jin(mcs4::uint12_t m) {
    mcs4::uint4_t r1 = l4b(m);
    mcs4::uint4_t r0 = r1 - (mcs4::uint4_t) 1;

    mcs4::uint4_t am = this->cpu->readRegister(r0);     // Middle and low bits from registers
    mcs4::uint4_t al = this->cpu->readRegister(r1);

    mcs4::uint12_t addr = (this->cpu->readCodePtr() << 8) | (am << 4) | al;
    this->cpu->writeCodePtr(addr);
}

void InstructionSet::jun(mcs4::uint12_t addr) {
    this->cpu->writeCodePtr(addr);
}

void InstructionSet::jms(mcs4::uint12_t addr) {
    // This has to be done before writing the code pointer as it relies on the current instruction to write the correct
    // address
    this->cpu->pushStack();
    this->cpu->writeCodePtr(addr);
}

void InstructionSet::inc(mcs4::uint12_t m) {
    mcs4::uint4_t r = l4b(m);     // Prevent overflow
    mcs4::uint4_t v = this->cpu->readRegister(r);   // Increment

    // If it overflows, set to zero
    if (v == 0xf) {
        v = 0;
    } else {
        v++;
    }

    // Write the value
    this->cpu->writeRegister(r, v);
}

void InstructionSet::isz(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::add(mcs4::uint12_t r) {
    mcs4::uint4_t v = this->cpu->readRegister(l4b(r)) +   // Mask to prevent registers overflow
                      this->cpu->readAccumulator() +
                      this->cpu->readCarry();
    this->cpu->writeAccumulatorAndCarry(v);
}

void InstructionSet::sub(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::ld(mcs4::uint12_t r) {
    mcs4::uint4_t v = this->cpu->readRegister(l4b(r));    // Mask to prevent registers overflow
    this->cpu->writeAccumulator(v);
}

void InstructionSet::xch(mcs4::uint12_t r) {
    mcs4::uint4_t acbr = this->cpu->readAccumulator();    // Accumulator buffer register

    mcs4::uint4_t v = this->cpu->readRegister(l4b(r));    // Mask to prevent registers overflow
    this->cpu->writeAccumulator(v);

    this->cpu->writeRegister(l4b(r), acbr);
}

void InstructionSet::bbl(mcs4::uint12_t v) {
    // TODO: Test
    // Write "return value" to accumulator
    this->cpu->writeAccumulator(l4b(v));
    // Transfer execution to the address from the stack
    mcs4::uint12_t addr = this->cpu->popStack();
    this->cpu->writeCodePtr(addr);
}

void InstructionSet::ldm(mcs4::uint12_t d) {
    mcs4::uint4_t value = l4b(d);   // Mask lower 4 bits

    this->cpu->writeAccumulator(value);
}

void InstructionSet::wrm(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::wmp(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::wrr(mcs4::uint12_t) {
    this->cpu->rom->writePort(this->cpu->readDataPtr(), this->cpu->readAccumulator());
}

void InstructionSet::wr0(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::wr1(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::wr2(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::wr3(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::sbm(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rdm(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rdr(mcs4::uint12_t) {
    // TODO: Why is data pointer 8-bit wide but address space is 16-bit? Check
    this->cpu->writeAccumulator(this->cpu->rom->readPort(this->cpu->readDataPtr()));
}

void InstructionSet::adm(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rd0(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rd1(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rd2(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::rd3(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::clb(mcs4::uint12_t) {
    this->cpu->writeAccumulatorAndCarry(0);
}

void InstructionSet::clc(mcs4::uint12_t) {
    this->cpu->writeCarry(0);
}

void InstructionSet::iac(mcs4::uint12_t) {
    mcs4::uint4_t v = this->cpu->readAccumulator();

    this->cpu->writeAccumulatorAndCarry(v + (mcs4::uint5_t) 1);
}

void InstructionSet::cmc(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::cma(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::ral(mcs4::uint12_t) {
    mcs4::uint5_t acc = this->cpu->readAccumulator();
    mcs4::uint1_t cy = this->cpu->readCarry();

    mcs4::uint5_t v = (acc << 1) | cy;
    this->cpu->writeAccumulatorAndCarry(v);
    // TODO: test
}

void InstructionSet::rar(mcs4::uint12_t) {
    mcs4::uint5_t acc = this->cpu->readAccumulator();
    mcs4::uint1_t cy = this->cpu->readCarry();

    mcs4::uint5_t v = (mask1bit(acc, 0) << 4) | (cy << 3) | (acc >> 1);
    this->cpu->writeAccumulatorAndCarry(v);
}

void InstructionSet::tcc(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::dac(mcs4::uint12_t) {
    mcs4::uint4_t v = this->cpu->readAccumulator();

    if (v == 0) {
        v = 0xf;
        this->cpu->writeCarry(0);
    } else {
        v--;
        this->cpu->writeCarry(1);
    }
    this->cpu->writeAccumulator(v);
    // TODO: The carry write doesn't seem right...
}

void InstructionSet::tcs(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::stc(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::daa(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::kbp(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::dcl(mcs4::uint12_t) {
    notImplErr(__FUNCTION__);
}

void InstructionSet::fim_src(mcs4::uint12_t m) {
    if ((m & 0x1) == 0) {
        this->fim(m);
    } else {
        this->src(m);
    }
}

void InstructionSet::fin_jin(mcs4::uint12_t m) {
    if ((m & 0x1) == 0) {
        this->fin(m);
    } else {
        this->jin(m);
    }
}

void InstructionSet::io(mcs4::uint12_t m) {
    instr_p instr = this->i_io[m];
    (this->*instr)(0);  // Modifier is unused
}

void InstructionSet::acc(mcs4::uint12_t m) {
    instr_p instr = this->i_acc[m];
    (this->*instr)(0);  // Modifier is unused
}

instr_p InstructionSet::fetchOpcode(uint8_t instruction) {
    mcs4::uint4_t opcode = h4b(instruction);
    return this->i[opcode];
}

bool InstructionSet::is2WordInstruction(uint8_t instruction) {
    mcs4::uint4_t hb = h4b(instruction);

    switch (hb) {
        case 0x2:   // FIM or SRC. First is 2 word, second isn't
            return l1b(instruction) == 0;
        case 0x1:
        case 0x4:
        case 0x5:
        case 0x7:
            return true;
        default:
            return false;
    }
}

bool InstructionSet::isJumpInstruction(uint8_t instruction) {
    mcs4::uint4_t hb = h4b(instruction);

    switch (hb) {
        case 0x1:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0xc:
            return true;
        default:
            return false;
    }

    // TODO: Check if it's everything
}

void InstructionSet::notImplErr(const char *opcode) {
    std::cerr << boost::to_upper_copy<std::string>(opcode) << " opcode not implemented" << std::endl;
}
