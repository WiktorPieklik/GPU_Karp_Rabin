#include "TextFileReader.cuh"

#include <fstream>
/**
 * Reads input string as path to text file (.txt) and return vector of strings.
 * Each vector's element represents each text line
 *
 * @param text
 */
TextFileReader::TextFileReader(std::experimental::filesystem::path  path) : Reader(), file_path(std::move(path)) {}

std::string TextFileReader::read()
{
    std::ifstream file(file_path);
    if(!file.is_open())
        throw std::runtime_error("Could not open file: " + file_path.string());
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

