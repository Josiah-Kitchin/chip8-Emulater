
cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
endif()


project(chip8_emu CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp" )

add_executable(chip ${SOURCES})

include_directories(./include)

target_compile_options(chip PRIVATE -Wall -Wextra -g)




