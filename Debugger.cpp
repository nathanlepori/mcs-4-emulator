//
// Created by nathan on 18.03.2019.
//

#include <iostream>

#include "Debugger.h"
#include "util.h"

void Debugger::cpuInspector(const CpuInfo *info) {
    auto instr_info = this->getInstructionInfo(info->raw_instr);
    if (instr_info != nullptr) {
        std::cout << "Current instruction: " << instr_info->first << " - " << instr_info->second << std::endl;
    }
}

Debugger::Debugger() = default;

instr_info *Debugger::getInstructionInfo(uint16_t instruction) {
    uint8_t opcode = l8b(instruction);
    if (this->i_info.count(opcode)) {
        return &this->i_info[opcode];
    } else {
        // Try to get the instruction by the high 4 bits (lower 4 are register index or other modifier)
        opcode = h4b(opcode);

        if (this->i_info.count(opcode)) {
            return &this->i_info[opcode];
        } else {
            return nullptr;
        }
    }
}

void Debugger::setChipset(Chipset *chipset) {
    Debugger::chipset = chipset;
}
