//
// Created by moh on 1/5/22.
//



#include "Chip8.h"
#include <fstream>
using namespace std;


void Chip8::loadProgram(string fileName) {
    ifstream myFile (fileName, ios::binary);
    if(myFile.is_open())
    {
        streampos fileSize = myFile.tellg();
        char* buffer = new char[fileSize];

        myFile.read(buffer, fileSize);
        myFile.close();

        for(long i = 0; i < fileSize; i++)
        {
            cout << buffer[i]
        }
    }

}