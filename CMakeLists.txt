cmake_minimum_required(VERSION 3.21)
project(CHIP8Emu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CHIP8Emu
        Chip8.cpp
        Chip8.h
        main.cpp)
