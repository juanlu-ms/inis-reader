cmake_minimum_required(VERSION 4.0)
project(lector_inis)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_executable(lector_inis src/main.cpp
        src/IniParser.cpp
        src/IniParser.h)
