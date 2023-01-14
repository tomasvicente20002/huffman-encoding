// Trabalho-11032720.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "Huffman.h"
#include <string>

using namespace std;

int main(int argc, char const* argv[])
{
    string readPath;
    string writePath;

    if (argc < 3)
    {
        cout << "Indique o ficheiro a ler: ";
        cin >> readPath;


        cout << "Indique o ficheiro a escrever: ";
        cin >> writePath;
    }
    else
    {
        readPath = GetStringForCharArray(argv[1]);
        writePath = GetStringForCharArray(argv[2]);
    }


    Huffman coder = Huffman(readPath, writePath);
    coder.Encode();
  
}