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

    std::map<uint8_t, instr_info> i_info = {
            {0b00000000, std::make_pair("NOP", "No Operation")},
            {0b0001, std::make_pair("JCN", "Jump Conditional")},
//            {0b0010RRR0, std::make_pair("FIM", "Fetch Immediate")},
//            {0b0010RRR1, std::make_pair("SRC", "Send Register Control")},
//            {0b0011RRR0, std::make_pair("FIN", "Fetch Indirect")},
//            {0b0011RRR1, std::make_pair("JIN", "Jump Indirect")},
            {0b0100, std::make_pair("JUN", "Jump Uncoditional")},
            {0b0101, std::make_pair("JMS", "Jump to Subroutine")},
            {0b0110, std::make_pair("INC", "Increment")},
            {0b0111, std::make_pair("ISZ", "Increment and Skip")},
            {0b1000, std::make_pair("ADD", "Add")},
            {0b1001, std::make_pair("SUB", "Subtract")},
            {0b1010, std::make_pair("LD", "Load")},
            {0b1011, std::make_pair("XCH", "Exchange")},
            {0b1100, std::make_pair("BBL", "Branch Back and Load")},
            {0b1101, std::make_pair("LDM", "Load Immediate")},
            {0b11100000, std::make_pair("WRM", "Write Main Memory")},
            {0b11100001, std::make_pair("WMP", "Write RAM Port")},
            {0b11100010, std::make_pair("WRR", "Write ROM Port")},
            {0b11100100, std::make_pair("WR0", "Write Status Char 0")},
            {0b11100101, std::make_pair("WR1", "Write Status Char 1")},
            {0b11100110, std::make_pair("WR2", "Write Status Char 2")},
            {0b11100111, std::make_pair("WR3", "Write Status Char 3")},
            {0b11101000, std::make_pair("SBM", "Subtract Main Memory")},
            {0b11101001, std::make_pair("RDM", "Read Main Memory")},
            {0b11101010, std::make_pair("RDR", "Read ROM Port")},
            {0b11101011, std::make_pair("ADM", "Add Main Memory")},
            {0b11101100, std::make_pair("RD0", "Read Status Char 0")},
            {0b11101101, std::make_pair("RD1", "Read Status Char 1")},
            {0b11101110, std::make_pair("RD2", "Read Status Char 2")},
            {0b11101111, std::make_pair("RD3", "Read Status Char 3")},
            {0b11110000, std::make_pair("CLB", "Clear Both")},
            {0b11110001, std::make_pair("CLC", "Clear Carry")},
            {0b11110010, std::make_pair("IAC", "Increment Accumulator")},
            {0b11110011, std::make_pair("CMC", "Complement Carry")},
            {0b11110100, std::make_pair("CMA", "Complement")},
            {0b11110101, std::make_pair("RAL", "Rotate Left")},
            {0b11110110, std::make_pair("RAR", "Rotate Right")},
            {0b11110111, std::make_pair("TCC", "Transfer Carry and Clear")},
            {0b11111000, std::make_pair("DAC", "Decrement Accumulator")},
            {0b11111001, std::make_pair("TCS", "Transfer Carry Subtract")},
            {0b11111010, std::make_pair("STC", "Set Carry")},
            {0b11111011, std::make_pair("DAA", "Decimal Adjust Accumulator")},
            {0b11111100, std::make_pair("KBP", "Keybord Process")},
            {0b11111101, std::make_pair("DCL", "Designate Command Line")}
    };

    /**
     * Returns a pair containing the mnemonic and a short text description of the given instruction.
     *
     * @param instruction
     * @return
     */
    instr_info *getInstructionInfo(uint16_t instruction);

public:
    Debugger();

    void setChipset(Chipset *chipset);

    void cpuInspector(const CpuInfo *info);

};


#endif //MCS_4_EMULATOR_DEBUGGER_H
