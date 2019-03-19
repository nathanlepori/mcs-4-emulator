#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/hex.hpp>

#include "config.h"
#include "Chipset.h"
#include "SpaceNotationProgramParser.h"

namespace po = boost::program_options;

unsigned short num_roms = 16;
std::string progfile;

void program_options(int argc, const char *const argv[]) {
    po::options_description desc("Options");
    desc.add_options()
            ("help", "Show help message")
            ("version", "Show version of this program")
            ("num-roms", po::value<unsigned short>()->default_value(num_roms),
             "Number of ROM chips installed on the board")
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

    if (vm.count("prog-file")) {
        progfile = vm["prog-file"].as<std::string>();
    }
}

int main(int argc, const char *const argv[]) {
    program_options(argc, argv);

    ProgramParser *parser = new SpaceNotationProgramParser(progfile);

    uint8_t prog[Rom::MAX_ROM_SZ];
    parser->parse(prog);

    auto *chipset = new Chipset(prog, (uint8_t) num_roms);
    auto *debugger = new Debugger();
    chipset->attachDebugger(debugger);

    auto t = chipset->powerOn();

    std::cout << "CPU thread started." << std::endl;

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "c") {
            chipset->signalCpu();
        } else if (cmd == "e") {
            break;
        }
    }

    t.join();
    std::cout << "CPU thread finished execution." << std::endl;

    delete parser;
    delete chipset;

    return 0;
}
