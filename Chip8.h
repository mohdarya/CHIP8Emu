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
    uint8_t memory[4096]{};

    uint8_t font[0x50] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                          0x20, 0x60, 0x20, 0x20, 0x70, // 1
                          0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                          0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                          0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                          0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                          0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                          0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                          0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                          0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                          0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                          0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                          0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                          0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                          0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                          0xF0, 0x80, 0xF0, 0x80, 0x80  } ;// F
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

    uint8_t getDelay();

    uint8_t key();

    void setDelay(uint8_t delay);

    void setSound(uint8_t sound);

    Chip8();
};


#endif //CHIP8EMU_CHIP8_H
