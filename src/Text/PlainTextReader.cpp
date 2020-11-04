#include "PlainTextReader.h"

/**
 * Reads input string
 *
 * @param text
 */


std::string PlainTextReader::read()
{
    return text;
}

PlainTextReader::PlainTextReader(std::string text) :text(std::move(text)) {

}
