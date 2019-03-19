cmake_minimum_required(VERSION 3.10)
project(mcs_4_emulator VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)

# Version info and other global configuration (injected from CMAKE)
configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(mcs_4_emulator main.cpp Cpu.cpp Cpu.h Ram.cpp Ram.h Chipset.cpp Chipset.h InstructionSet.cpp InstructionSet.h util.cpp util.h Rom.cpp Rom.h mcs4_stdint.h ProgramParser.cpp ProgramParser.h SpaceNotationProgramParser.cpp SpaceNotationProgramParser.h config.h.in CpuInfo.h Debugger.cpp Debugger.h)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS program_options)

find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

# Note: a target should be already defined using 'add_executable' or 'add_library'
target_link_libraries(mcs_4_emulator ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
