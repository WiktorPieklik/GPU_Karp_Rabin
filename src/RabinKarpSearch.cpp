//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "RabinKarpSearch.h"
#include "StandardHash.h"

#include <tuple>

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
    std::tuple<long long int, long long int> hashes = hash
            .forBase(base)
            .getPolyValues(pattern, text[index].substr(currentWindowPosition, pattern.size()));
    patternHash = std::get<0>(hashes) % this->prime;
    tmpHash = std::get<1>(hashes) % this->prime;
}

template <typename Hash>
void RabinKarpSearch<Hash>::calculateRollingHash()
{
    if(this->currentWindowPosition != 0)
    {
        tmpHash = (tmpHash - this->mostSignificantWeight * text[index][currentWindowPosition - 1]) * this->base + text[index][currentWindowPosition + pattern.size() - 1];
        tmpHash = tmpHash % this->prime;

        if(tmpHash < 0)
        {
            tmpHash = tmpHash + this->prime;
        }
    }
    else
    {
        if(index < text.size())
        {
            tmpHash = calculateHash(text[index].substr(currentWindowPosition, pattern.size()));
        }
    }
}

template <typename Hash>
void RabinKarpSearch<Hash>::moveWindow()
{
    ++this->currentWindowPosition;
    if(this->currentWindowPosition + pattern.size() > text[index].size())
    {
        ++this->index;
        this->currentWindowPosition = 0;
    }
}

template <typename Hash>
std::vector<int> RabinKarpSearch<Hash>::search()
{
    while(index < text.size())
    {
        if(tmpHash == patternHash)
        {
            if(pattern == text[index].substr(currentWindowPosition, pattern.size()))
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