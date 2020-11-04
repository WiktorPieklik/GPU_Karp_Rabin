#include "RabinKarpSearch.h"
#include "StandardHash.h"

#include <tuple>

template <typename Hash>
RabinKarpSearch<Hash>::RabinKarpSearch(std::string file, const std::string& pattern): file(file), pattern(pattern)
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
std::vector<std::string> RabinKarpSearch<Hash>::readText()
{
    std::unique_ptr<Reader> reader = TextReaderFactory::forText(file);
    if(!reader)
        throw std::runtime_error("Couldn't create a reader!");
    return reader->read();
}

template <typename Hash>
long long int RabinKarpSearch<Hash>::calculateHash(const std::string& text)
{
    Hash hash = Hash();
    long long hashVal = hash
            .forBase(base)
            .getPolyValue(text);

    return hashVal % this->prime;

}

template <typename Hash>
void RabinKarpSearch<Hash>::calculateHashes()
{
    Hash hash = Hash();
    std::tuple<long long, long long> hashes = hash
            .forBase(base)
            .getPolyValues(pattern, text[lineNo].substr(currentWindowPosition, pattern.size()));
    patternHash = std::get<0>(hashes) % this->prime;
    windowHash = std::get<1>(hashes) % this->prime;
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
std::vector<size_t> RabinKarpSearch<Hash>::search()
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