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

}

char Chip8::getFirstCode(uint8_t instruction) {
    int first4Bit = (instruction >> (4*1)) & 0xf;
    stringstream  stream;
    stream << hex <<first4Bit ;
    return stream.str()[0];
}





