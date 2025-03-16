cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug) 

project(chip8_emu CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(SFML 2.5 REQUIRED graphics window system audio)

add_executable(chip ${SOURCES})

target_include_directories(chip PRIVATE ./include) 

target_compile_options(chip PRIVATE -Wall -Wextra -g)

target_link_libraries(chip sfml-graphics sfml-window sfml-system sfml-audio)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(chip PRIVATE DEBUG_BUILD)
endif()
