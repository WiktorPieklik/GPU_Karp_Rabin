//
// Created by Wiktor Pieklik on 15/10/2020.
//

#include "Text/TextFileReader.h"

TextFileReader::TextFileReader(const std::string &text) : Reader(text), file(text) {}

std::vector<std::string> & TextFileReader::read()
{
    std::string line;
    while(std::getline(file, line))
    {
        textVector.push_back(line);
    }

    return textVector;
}

