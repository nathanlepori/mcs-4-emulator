cmake_minimum_required(VERSION 3.10)
project(mcs_4_emulator VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Version info and other global configuration (injected from CMAKE)
configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(mcs_4_emulator main.cpp core/peripherals/Cpu.cpp core/peripherals/Cpu.h core/peripherals/Ram.cpp core/peripherals/Ram.h core/Chipset.cpp core/Chipset.h core/InstructionSet.cpp core/InstructionSet.h util.cpp util.h core/peripherals/Rom.cpp core/peripherals/Rom.h mcs4_stdint.h ProgramParser.cpp ProgramParser.h SpaceNotationProgramParser.cpp SpaceNotationProgramParser.h config.h.in CpuInfo.h Debugger.cpp Debugger.h)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS program_options)

find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

# Note: a target should be already defined using 'add_executable' or 'add_library'
target_link_libraries(mcs_4_emulator ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
