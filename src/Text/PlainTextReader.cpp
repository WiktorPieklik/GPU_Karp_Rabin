//
// Created by Wiktor Pieklik on 15/10/2020.
//

#include "Text/PlainTextReader.h"

PlainTextReader::PlainTextReader(const std::string &text) : Reader(text)
{
    textVector.push_back(text);
}

std::vector<std::string>& PlainTextReader::read()
{
    return textVector;
}
