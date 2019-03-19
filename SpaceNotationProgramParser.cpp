//
// Created by nathan on 15.01.2019.
//

#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "SpaceNotationProgramParser.h"
#include "mcs4_stdint.h"
#include "Rom.h"

SpaceNotationProgramParser::SpaceNotationProgramParser(std::string filename) {
    if (filename.length() == 0) {
        std::cerr << "No program file provided. ROM chip will be empty." << std::endl;
        return;
    }

    this->progfile.open(filename, std::ios::in);

    if (this->progfile.fail()) {
        std::cerr << "Couldn't open program file " << filename << ". ROM chip will be empty." << std::endl;
    }
}

void SpaceNotationProgramParser::parse(uint8_t *prog) {
    // Clear array
    std::fill_n(prog, Rom::MAX_ROM_SZ, 0);

    mcs4::uint12_t addr = 0;
    std::string line;

    while (std::getline(this->progfile, line)) {
        if (line.length() == 0) {
            continue;   // Skip if empty
        }
        if (boost::starts_with(line, "*=$")) {    // If it starts with this prefix it's an address offset line
            std::string addr_str = line.substr(3);
            addr = static_cast<mcs4::uint12_t>(std::stoul(addr_str, nullptr, 16));
        } else {
            std::vector<std::string> hex_strs;
            boost::split(hex_strs, line, boost::is_space());


            std::vector<std::string>::iterator it;
            for (it = hex_strs.begin(); it != hex_strs.end(); it++, addr++) {
                std::string hex_str = *it;

                // Hex to uint conversion
                auto code = static_cast<uint8_t>(std::stoul(hex_str, nullptr, 16));

                // Assign the machine code
                prog[addr] = code;
            }
        }
    }
}
