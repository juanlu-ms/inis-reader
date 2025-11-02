cmake_minimum_required(VERSION 3.15)
project(lector_inis)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_executable(lector_inis src/main.cpp
        src/IniParser.cpp
        src/IniParser.h)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(ini_parser_tests tests/IniParserTest.cpp src/IniParser.cpp)

target_link_libraries(ini_parser_tests gtest_main)

include(GoogleTest)
gtest_add_tests(TARGET ini_parser_tests)
