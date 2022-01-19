//
// Created by moh on 1/5/22.
//



#include "Chip8.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <random>

using namespace std;

const unsigned int START_ADDRESS = 0x200;

void Chip8::loadProgram(string fileName) {

    ifstream myFile(fileName, ios::binary | ios::ate);

    if (myFile.is_open()) {

        streampos fileSize = myFile.tellg();
        char *buffer = new char[fileSize];

        myFile.seekg(0, ios::beg);
        myFile.read(buffer, fileSize);
        myFile.close();


        for (long i = 0; i < fileSize; i++) {
            memory[START_ADDRESS + i] = buffer[i];

        }

        delete[] buffer;
    }

}

Chip8::Chip8() {
    for (int i = 0; i < 0x50; i++) {
        memory[i] = font[i];
    }

}

void Chip8::runInstruction(uint8_t instructionFirst, uint8_t instructionSecond) {
    char firstInstruction = getFirstCode(instructionFirst);
    int secondNibble = (instructionFirst >> (4 * 2));
    int thirdNibble = (instructionSecond >> (4 * 1));
    int fourthNibble = (instructionSecond >> (4 * 2));

    switch (firstInstruction) {
        case '0':
            if (instructionToHex(instructionSecond) == "e0") {
                clearScreen();
            } else if (instructionToHex(instructionSecond) == "ee") {
                programCounter = stack.top();
                stack.pop();
            }
            break;
        case '1':
            programCounter = secondNibble + instructionSecond;
            break;
        case '2':
            stack.push(programCounter);
            programCounter = secondNibble + instructionSecond;
            break;
        case '3':
            if (registers[secondNibble] == instructionSecond) {
                programCounter += 2;
            }
            break;
        case '4':
            if (registers[secondNibble] != instructionSecond) {
                programCounter += 2;
            }
            break;
        case '5':
            if (registers[secondNibble] == registers[thirdNibble]) {
                programCounter += 2;
            }
            break;
        case '6':
            registers[secondNibble] = instructionSecond;
            break;
        case '7':
            registers[secondNibble] += instructionSecond;
            break;
        case '8':
            switch (intToHex(fourthNibble)) {
                case '0':
                    registers[secondNibble] = registers[thirdNibble];
                    break;
                case '1':
                    registers[secondNibble] |= registers[thirdNibble];
                    break;
                case '2':
                    registers[secondNibble] &= registers[thirdNibble];
                    break;
                case '3':
                    registers[secondNibble] ^= registers[thirdNibble];
                    break;
                case '4':
                    uint16_t sum;
                    sum = registers[secondNibble] + registers[thirdNibble];
                    if (sum > 255U) {
                        registers[0xF] = 1;
                    } else {
                        registers[0xF] = 0;
                    }
                    registers[secondNibble] = sum & 0xFFu;
                    break;
                case '5':
                    if (registers[secondNibble] > registers[thirdNibble]) {
                        registers[0xF] = 1;
                    } else {
                        registers[0xF] = 0;
                    }

                    registers[secondNibble] -= registers[thirdNibble];
                    break;
                case '6':
                    registers[0xf] = registers[thirdNibble] & 0x1u;
                    registers[thirdNibble] >>= 1;
                    break;
                case '7':
                    if (registers[thirdNibble] > registers[secondNibble]) {
                        registers[0xF] = 1;
                    } else {
                        registers[0xF] = 0;
                    }

                    registers[secondNibble] = registers[thirdNibble] - registers[secondNibble];
                    break;
                case 'e':
                    registers[0xf] = (registers[thirdNibble] & 0x80u) >> 7u;
                    registers[thirdNibble] <<= 1;
                    break;
            }
            break;
        case '9':
            if (registers[secondNibble] != registers[thirdNibble]) {
                programCounter += 2;
            }
            break;
        case 'a':
            indexReg = secondNibble + instructionSecond;
            break;
        case 'b':
            programCounter = registers[0x0] + secondNibble + instructionSecond;
            break;
        case 'c':
            registers[secondNibble] = generateRand() & instructionSecond;
            break;
        case 'd':
            draw(registers[secondNibble], registers[thirdNibble], fourthNibble);
            break;
        case 'e':

            if (instructionToHex(instructionSecond) == "9e") {
                if (key() == registers[secondNibble]) {
                    programCounter += 2;
                }

            } else {

                if (key() != registers[secondNibble]) {
                    programCounter += 2;
                }

            }

        case 'f':

            if (instructionToHex(instructionSecond) == "07") {
                registers[secondNibble] = getDelay();

            }
            if (instructionToHex(instructionSecond) == "0a") {
                registers[secondNibble] = getKey();
            }
            if (instructionToHex(instructionSecond) == "15") { setDelay(registers[secondNibble]); }

            if (instructionToHex(instructionSecond) == "18") { setSound(registers[secondNibble]); }

            if (instructionToHex(instructionSecond) == "1e") { indexReg += registers[secondNibble]; }

            if (instructionToHex(instructionSecond) == "29") {
                indexReg = 0x5 * registers[secondNibble];
            }
            if (instructionToHex(instructionSecond) == "33") {
                uint8_t value = registers[secondNibble];

                // Ones-place
                memory[indexReg + 2] = value % 10;
                value /= 10;

                // Tens-place
                memory[indexReg + 1] = value % 10;
                value /= 10;

                // Hundreds-place
                memory[indexReg] = value % 10;
            }
            if (instructionToHex(instructionSecond) == "55") {
                uint16_t startingAddress = indexReg;
                for (int i = 0x0; i < secondNibble; i++) {
                    memory[startingAddress] = registers[i];
                    startingAddress += 1;
                }
            }
            if (instructionToHex(instructionSecond) == "65") {
                uint16_t startingAddress = indexReg;
                for (int i = 0x0; i < secondNibble; i++) {
                    registers[i] = memory[startingAddress];
                    startingAddress += 1;
                }
            }
    }


}

char Chip8::getFirstCode(uint8_t instruction) {
    int first4Bit = (instruction >> (4 * 1)) & 0xf;
    stringstream stream;
    stream << hex << first4Bit;
    return stream.str()[0];
}


std::string Chip8::instructionToHex(uint8_t instruction) {
    stringstream stream;
    stream << hex << (int) instruction;
    return stream.str();
}

char Chip8::intToHex(int instruction) {
    stringstream stream;
    stream << hex << instruction;
    return stream.str()[0];
}

int Chip8::generateRand() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist255(0, 255);

    return (int) dist255(rng);
}


void Chip8::setDelay(uint8_t delay) {
    delayTimer = delay;

}

void Chip8::setSound(uint8_t sound) {
    soundTimer = sound;

}


void Chip8::clearScreen() {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            pixels[i][j] = 0;

        }
    }
}


void Chip8::draw(uint8_t x, uint8_t y, uint8_t height) {

}

uint8_t Chip8::getKey() {


}

uint8_t Chip8::key() {


}

uint8_t Chip8::getDelay() {


}