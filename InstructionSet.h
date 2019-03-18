//
// Created by nathan on 19.12.2018.
//

#ifndef MCS_4_EMULATOR_INSTRUCTIONSET_H
#define MCS_4_EMULATOR_INSTRUCTIONSET_H

#include <stdint.h>

#include "Cpu.h"
#include "mcs4_stdint.h"

class Cpu;
class InstructionSet;

/**
 * Holds an instruction as function pointer (after the fetch phase). Instructions are differentiated only by the first
 * four bits (different instructions having the same four bits are handled in wrapper functions) and are at most 2 bytes
 * long (for 2-word instructions). Hence the argument is 12-bits long.
 */
typedef void (InstructionSet::*instr_p)(mcs4::uint12_t);

class InstructionSet {
private:
    Cpu *const cpu;

    void notImplErr(const char *opcode);

    // Instructions
    // 2 word instructions take a 12 bit modifier. In order to make it fit it's necessary to have at least 16 bits

    void nop(mcs4::uint12_t);

    void jcn(mcs4::uint12_t);

    void fim(mcs4::uint12_t);

    void src(mcs4::uint12_t);

    void fin(mcs4::uint12_t);

    void jin(mcs4::uint12_t);

    void jun(mcs4::uint12_t);

    void jms(mcs4::uint12_t);

    void inc(mcs4::uint12_t);

    void isz(mcs4::uint12_t);

    void add(mcs4::uint12_t);

    void sub(mcs4::uint12_t);

    void ld(mcs4::uint12_t);

    void xch(mcs4::uint12_t);

    void bbl(mcs4::uint12_t);

    void ldm(mcs4::uint12_t);

    void wrm(mcs4::uint12_t);

    void wmp(mcs4::uint12_t);

    void wrr(mcs4::uint12_t);

    void wr0(mcs4::uint12_t);

    void wr1(mcs4::uint12_t);

    void wr2(mcs4::uint12_t);

    void wr3(mcs4::uint12_t);

    void sbm(mcs4::uint12_t);

    void rdm(mcs4::uint12_t);

    void rdr(mcs4::uint12_t);

    void adm(mcs4::uint12_t);

    void rd0(mcs4::uint12_t);

    void rd1(mcs4::uint12_t);

    void rd2(mcs4::uint12_t);

    void rd3(mcs4::uint12_t);

    void clb(mcs4::uint12_t);

    void clc(mcs4::uint12_t);

    void iac(mcs4::uint12_t);

    void cmc(mcs4::uint12_t);

    void cma(mcs4::uint12_t);

    void ral(mcs4::uint12_t);

    void rar(mcs4::uint12_t);

    void tcc(mcs4::uint12_t);

    void dac(mcs4::uint12_t);

    void tcs(mcs4::uint12_t);

    void stc(mcs4::uint12_t);

    void daa(mcs4::uint12_t);

    void kbp(mcs4::uint12_t);

    void dcl(mcs4::uint12_t);

    // Switch between instructions with the same opcode here
    void fim_src(mcs4::uint12_t);

    void fin_jin(mcs4::uint12_t);

    void io(mcs4::uint12_t);    // Includes WRM, WMP, WRR, WR0, WR1, WR2, WR3, SBM, RDM, RDR, ADM, RD0, RD1, RD2, RD3

    void acc(mcs4::uint12_t); // Includes CLB, CLC, IAC, CMC, CMA, RAL, RAR, TCC, DAC, TCS, STC, DAA, KBP, DCL

    // Lookup tables
    const instr_p i[16] = {
            &InstructionSet::nop,
            &InstructionSet::jcn,
            &InstructionSet::fim_src,
            &InstructionSet::fin_jin,
            &InstructionSet::jun,
            &InstructionSet::jms,
            &InstructionSet::inc,
            &InstructionSet::isz,
            &InstructionSet::add,
            &InstructionSet::sub,
            &InstructionSet::ld,
            &InstructionSet::xch,
            &InstructionSet::bbl,
            &InstructionSet::ldm,
            &InstructionSet::io,
            &InstructionSet::acc
    };

    // IO and RAM instructions
    const instr_p i_io[16] = {
            &InstructionSet::wrm,
            &InstructionSet::wmp,
            &InstructionSet::wrr,
            nullptr,        // This opcode is missing for some reason
            &InstructionSet::wr0,
            &InstructionSet::wr1,
            &InstructionSet::wr2,
            &InstructionSet::wr3,
            &InstructionSet::sbm,
            &InstructionSet::rdm,
            &InstructionSet::rdr,
            &InstructionSet::adm,
            &InstructionSet::rd0,
            &InstructionSet::rd1,
            &InstructionSet::rd2,
            &InstructionSet::rd3
    };

    // Accumulator group instructions
    const instr_p i_acc[14] = {
            &InstructionSet::clb,
            &InstructionSet::clc,
            &InstructionSet::iac,
            &InstructionSet::cmc,
            &InstructionSet::cma,
            &InstructionSet::ral,
            &InstructionSet::rar,
            &InstructionSet::tcc,
            &InstructionSet::dac,
            &InstructionSet::tcs,
            &InstructionSet::stc,
            &InstructionSet::daa,
            &InstructionSet::kbp,
            &InstructionSet::dcl
    };

public:
    explicit InstructionSet(Cpu *const cpu);

    /**
     * Fetches an opcode high 4 bits of an instruction
     *
     * @param instruction
     * @return
     */
    instr_p fetchOpcode(uint8_t instruction);

    bool is2WordInstruction(uint8_t instruction);

    bool isJumpInstruction(uint8_t instruction);
};


#endif //MCS_4_EMULATOR_INSTRUCTIONSET_H
