#include <iostream>
#include "Chipset.h"
#include "SpaceNotationProgramParser.h"

int main() {
    ProgramParser *parser = new SpaceNotationProgramParser("../program.mcs4");

    uint8_t prog[Rom::ROM_SZ];
    parser->parse(prog);

    auto *chipset = new Chipset(prog);

    chipset->powerOn();

    return 0;
}
