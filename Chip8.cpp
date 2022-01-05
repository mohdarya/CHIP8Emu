//
// Created by moh on 1/5/22.
//



#include "Chip8.h"
#include <fstream>
#include <iostream>
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