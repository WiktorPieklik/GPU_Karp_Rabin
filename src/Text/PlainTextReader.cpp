//
// Created by Wiktor Pieklik on 15/10/2020.
//

#include "PlainTextReader.h"

/**
 * Reads input string and passes it further as one element vector
 *
 * @param text
 */
PlainTextReader::PlainTextReader(const std::string &text) : Reader(text)
{
    textVector.push_back(text);
}

std::vector<std::string>& PlainTextReader::read()
{
    return textVector;
}
