//
// Created by moh on 1/5/22.
//
#include <cstdint>
#include <string>
#include <stack>
#ifndef CHIP8EMU_CHIP8_H
#define CHIP8EMU_CHIP8_H


class Chip8 {

private:
    uint8_t registers[16]{};
    uint8_t memory [4096]{};
    uint16_t indexReg;
    uint16_t programCounter;
    std::stack<uint16_t> stack;
    uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t keys[16]{};
    uint32_t pixels[64][32]{};

public:
    void loadProgram(std::string fileName);
    void runInstruction(uint8_t instructionFirst, uint8_t instructionSecond);
    char getFirstCode(uint8_t instruction);
    std::string instructionToHex(uint8_t instruction);
    void clearScreen();
    char intToHex(int instruction);

    int generateRand();

    void draw(uint8_t x, uint8_t y, uint8_t height);

    uint8_t getKey();
};


#endif //CHIP8EMU_CHIP8_H
