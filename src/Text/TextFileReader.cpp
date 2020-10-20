#include "Text/TextFileReader.h"

/**
 * Reads input string as path to text file (.txt) and return vector of strings.
 * Each vector's element represents each text line
 *
 * @param text
 */
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

