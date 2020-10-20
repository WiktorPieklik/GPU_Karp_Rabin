#include "Text/TextReaderFactory.h"
#include "Text/FileNotFoundException.h"
#include "Text/PlainTextReader.h"
#include "Text/TextFileReader.h"

bool TextReaderFactory::fileExists(std::string& text)
{
    struct stat buffer{};

    return (stat (text.c_str(), &buffer) == 0);
}

bool TextReaderFactory::isTxtFile(std::string& text)
{
    std::regex regex(".*(.txt)$");
    std::cmatch match;

    return std::regex_match(text.c_str(), match, regex);
}

/**
 * Determines if given string is path to file or either sample string to be processed.
 * Every file that ends with .txt is considered to be path to file.
 *
 * @param text
 * @return Reader*
 */
Reader* TextReaderFactory::forText(std::string text)
{
    if(isTxtFile(text))
    {
        if(fileExists(text))
        {
            return new TextFileReader(text);
        }

        throw FileNotFoundException(text + " cannot be found!");
    }
    else
    {
        return new PlainTextReader(text);
    }
}
