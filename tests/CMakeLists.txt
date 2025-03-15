cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(test_chip CXX)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

find_package(SFML 2.5 REQUIRED graphics window system)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(chip_test ${SOURCES} ${TEST_SOURCES})

target_include_directories(chip_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(
        chip_test PRIVATE 
        gtest 
        gtest_main
        sfml-graphics
        sfml-window
        sfml-system
    )

target_compile_options(chip_test PRIVATE -Wall -Wextra -g)

