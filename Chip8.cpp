//
// Created by moh on 1/5/22.
//



#include "Chip8.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <iomanip>
using namespace std;

const unsigned int START_ADDRESS = 0x200;
void Chip8::loadProgram(string fileName) {

    ifstream myFile (fileName, ios::binary| ios::ate);

    if(myFile.is_open())
    {

        streampos fileSize = myFile.tellg();
        char* buffer = new char[fileSize];

        myFile.seekg(0, ios::beg);
        myFile.read(buffer, fileSize);
        myFile.close();


        for(long i = 0; i < fileSize; i++)
        {
            memory[START_ADDRESS + i] = buffer[i];

        }

        delete[] buffer;
    }

}

void Chip8::runInstruction(uint8_t instructionFirst, uint8_t instructionSecond) {
    char firstInstruction = getFirstCode(instructionFirst);
    int secondNibble = (instructionFirst >> (4*2));
    int thirdNibble = (instructionSecond >> (4*1));
    int fourthNibble = (instructionSecond >> (4*2));

    switch (firstInstruction) {
        case '0':
            if(instructionToHex(instructionSecond) == "e0")
            {
                clearScreen();
            }
            else if(instructionToHex(instructionSecond) == "ee")
            {
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
            if(registers[secondNibble] == instructionSecond)
            {
                programCounter += 2;
            }
            break;
        case '4':
            if(registers[secondNibble]  != instructionSecond)
            {
                programCounter += 2;
            }
            break;
        case '5':
            if(registers[secondNibble]  == registers[thirdNibble])
            {
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
                    if (sum > 255U)
                    {
                        registers[0xF] = 1;
                    }
                    else
                    {
                        registers[0xF] = 0;
                    }
                    registers[secondNibble] = sum & 0xFFu;
                    break;
                case '5':
                    if (registers[secondNibble] > registers[thirdNibble])
                    {
                        registers[0xF] = 1;
                    }
                    else
                    {
                        registers[0xF] = 0;
                    }

                    registers[secondNibble] -= registers[thirdNibble];
                    break;
                case '6':
                    registers[0xf] = registers[thirdNibble] & 0x1u ;
                    registers[thirdNibble] >>= 1;
                    break;
                case '7':
                    if (registers[thirdNibble] > registers[secondNibble])
                    {
                        registers[0xF] = 1;
                    }
                    else
                    {
                        registers[0xF] = 0;
                    }

                    registers[secondNibble] = registers[thirdNibble] - registers[secondNibble];
                    break;
                case 'e':
                    registers[0xf] = (registers[thirdNibble] & 0x80u) >> 7u;
                    registers[thirdNibble] <<= 1;
                    break;
            }

    }
}

char Chip8::getFirstCode(uint8_t instruction) {
    int first4Bit = (instruction >> (4*1)) & 0xf;
    stringstream  stream;
    stream << hex <<first4Bit ;
    return stream.str()[0];
}

void Chip8::clearScreen() {

}

std::string Chip8::instructionToHex(uint8_t instruction) {
    stringstream  stream;
    stream << hex << (int) instruction ;
    return stream.str();
}

char Chip8::intToHex(int instruction) {
    stringstream  stream;
    stream << hex <<  instruction ;
    return stream.str()[0];
}




