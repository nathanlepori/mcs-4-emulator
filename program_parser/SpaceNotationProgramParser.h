//
// Created by nathan on 15.01.2019.
//

#ifndef MCS_4_EMULATOR_SPACENOTATIONPROGRAMPARSER_H
#define MCS_4_EMULATOR_SPACENOTATIONPROGRAMPARSER_H

#include <fstream>
#include "ProgramParser.h"

class SpaceNotationProgramParser: public ProgramParser {
public:
    explicit SpaceNotationProgramParser(std::string filename);

    void parse(uint8_t *prog) override;
private:
    std::ifstream progfile;
};


#endif //MCS_4_EMULATOR_SPACENOTATIONPROGRAMPARSER_H
