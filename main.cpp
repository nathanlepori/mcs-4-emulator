#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/hex.hpp>

#include "config.h"
#include "core/Chipset.h"
#include "program_parser/SpaceNotationProgramParser.h"

namespace po = boost::program_options;

unsigned short num_roms = 16;
unsigned short num_rams = 16;
bool debug = false;
std::string progfile;

void program_options(int argc, const char *const argv[]) {
    po::options_description desc("Options");
    desc.add_options()
            ("help", "Show help message")
            ("version", "Show version of this program")
            ("num-roms", po::value<unsigned short>()->default_value(num_roms),
             "Number of ROM chips installed on the board")
            ("num-rams", po::value<unsigned short>()->default_value(num_rams),
             "Number of RAM chips installed on the board")
             ("debug", "Attach debugger")
            ("prog-file", po::value<std::string>(),
             "Program to be loaded into ROM and run by the processor");

    po::positional_options_description pos_desc;
    pos_desc.add("prog-file", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
                      .options(desc)
                      .positional(pos_desc)
                      .run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << "MCS-4 Emulator (v" << PROJECT_VERSION << ")" << std::endl;
        std::cout << "Usage: " << argv[0] << " [options] {program file}" << std::endl;
        std::cout << desc << std::endl;
        exit(0);
    }

    if (vm.count("version")) {
        std::cout << "v" << PROJECT_VERSION << std::endl;
        exit(0);
    }

    if (vm.count("num-roms")) {
        num_roms = vm["num-roms"].as<unsigned short>();
    }

    if (vm.count("num-rams")) {
        num_rams = vm["num-rams"].as<unsigned short>();
    }

    if (vm.count("debug")) {
        debug = true;
    }

    if (vm.count("prog-file")) {
        progfile = vm["prog-file"].as<std::string>();
    }
}

int main(int argc, const char *const argv[]) {
    program_options(argc, argv);

    // Parse program from file
    ProgramParser *parser = new SpaceNotationProgramParser(progfile);
    uint8_t prog[Rom::MAX_ROM_SZ];
    parser->parse(prog);
    delete parser;


    auto *chipset = new Chipset(prog, (uint8_t) num_roms, (uint8_t) num_rams);
    auto *debugger = new Debugger();

    // DEBUG
    debugger->setBreakpoint(0x2);
    debugger->setBreakpoint(0xa);

    if (debug) {
        chipset->attachDebugger(debugger);
    }

    // Start chipset
    chipset->powerOn();

    delete chipset;
    delete debugger;

    return 0;
}
