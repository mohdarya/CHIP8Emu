//
// Created by moh on 1/5/22.
//
#include <cstdint>
#include <string>
#ifndef CHIP8EMU_CHIP8_H
#define CHIP8EMU_CHIP8_H


class Chip8 {

private:
    uint8_t registers[16]{};
    uint8_t memory [4096]{};
    uint16_t indexReg;
    uint16_t programCounter;
    uint16_t stack[16]{};
    uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t keys[16]{};
    uint32_t pixels[64][32]{};

public:
    void loadProgram(std::string fileName);
};


#endif //CHIP8EMU_CHIP8_H
