#include "RabinKarpSearch.h"
#include "Hash/StandardHash.h"

#include <utility>

template <typename Hash>
RabinKarpSearch<Hash>::RabinKarpSearch(const std::string& file, const std::string& pattern): file(file), pattern(pattern)
{
    init();
}

template <typename Hash>
void RabinKarpSearch<Hash>::init()
{
    text = readText();
    calculateHashes();
    for(size_t i = 1; i < pattern.size(); ++i)
    {
        mostSignificantWeight *= this->base;
    }
}

template <typename Hash>
std::vector<std::string>& RabinKarpSearch<Hash>::readText()
{
    Reader* reader = TextReaderFactory::forText(file);
    return reader->read();
}

template <typename Hash>
long long int RabinKarpSearch<Hash>::calculateHash(const std::string& text)
{
    Hash hash = Hash();
    long long int hashVal = hash
            .forBase(base)
            .getPolyValue(text);

    return hashVal % this->prime;

}

template <typename Hash>
void RabinKarpSearch<Hash>::calculateHashes()
{
    Hash hash = Hash();
    long long int* hashes = hash
            .forBase(base)
            .getPolyValues(pattern, text[lineNo].substr(currentWindowPosition, pattern.size()));
    patternHash = hashes[0] % this->prime;
    windowHash = hashes[1] % this->prime;
}

template <typename Hash>
void RabinKarpSearch<Hash>::calculateRollingHash()
{
    if(this->currentWindowPosition != 0)
    {
        windowHash = (windowHash - this->mostSignificantWeight * text[lineNo][currentWindowPosition - 1]) * this->base + text[lineNo][currentWindowPosition + pattern.size() - 1];
        windowHash = windowHash % this->prime;

        if(windowHash < 0)
        {
            windowHash = windowHash + this->prime;
        }
    }
    else
    {
        if(lineNo < text.size())
        {
            windowHash = calculateHash(text[lineNo].substr(currentWindowPosition, pattern.size()));
        }
    }
}

template <typename Hash>
void RabinKarpSearch<Hash>::moveWindow()
{
    ++this->currentWindowPosition;
    if(this->currentWindowPosition + pattern.size() > text[lineNo].size())
    {
        ++this->lineNo;
        this->currentWindowPosition = 0;
    }
}

template <typename Hash>
std::vector<int> RabinKarpSearch<Hash>::search()
{
    while(lineNo < text.size())
    {
        if(windowHash == patternHash)
        {
            if(pattern == text[lineNo].substr(currentWindowPosition, pattern.size()))
            {
                //match found
                matches.push_back(currentWindowPosition);
            }
        }
        moveWindow();
        calculateRollingHash();
    }

    return matches;
}

template class RabinKarpSearch<StandardHash>;