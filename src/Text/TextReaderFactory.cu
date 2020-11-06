#include "TextReaderFactory.cuh"
#include "FileNotFoundException.cuh"
#include "PlainTextReader.cuh"
#include "TextFileReader.cuh"

#include <experimental/filesystem>

/**
 * Determines if given string is path to file or either sample string to be processed.
 * Every file that ends with .txt is considered to be path to file.
 *
 * @param text
 * @return Reader*
 */
std::unique_ptr<Reader> TextReaderFactory::forText(const std::string& text)
{
    std::experimental::filesystem::path path(text);
    if(path.extension() == ".txt")
    {
        if(std::experimental::filesystem::exists(path))
        {
            return std::make_unique<TextFileReader>(text);
        }

        throw FileNotFoundException(text + " cannot be found!");
    }
    else
    {
        return std::make_unique<PlainTextReader>(text);
    }
}
