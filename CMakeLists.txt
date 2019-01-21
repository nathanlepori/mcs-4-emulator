cmake_minimum_required(VERSION 3.13)
project(mcs_4_emulator)

set(CMAKE_CXX_STANDARD 17)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(mcs_4_emulator main.cpp Cpu.cpp Cpu.h Ram.cpp Ram.h Chipset.cpp Chipset.h InstructionSet.cpp InstructionSet.h util.cpp util.h Rom.cpp Rom.h mcs4_stdint.h ProgramParser.cpp ProgramParser.h SpaceNotationProgramParser.cpp SpaceNotationProgramParser.h RomChip.cpp RomChip.h RamChip.cpp RamChip.h)
