//
// Created by Wiktor Pieklik on 16/10/2020.
//

#include "RabinKarpSearch.h"
#include "../header/StandardHash.h"

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
}

template <typename Hash>
std::vector<std::string>& RabinKarpSearch<Hash>::readText()
{
    Reader* reader = TextReaderFactory::forText(file);
    return reader->read();
}

template <typename Hash>
int RabinKarpSearch<Hash>::calculateHash(const std::string& text)
{
    Hash hash = Hash();
    int hashVal = hash
            .forBase(base)
            .getPolyValue(text);

    return hashVal % this->prime;

}

template <typename Hash>
void RabinKarpSearch<Hash>::calculateHashes()
{
    Hash hash = Hash();
    int* hashes = hash
            .forBase(base)
            .getPolyValues(pattern, text[index].substr(currentWindowPosition, pattern.size()));
    patternHash = hashes[0] % this->prime;
    tmpHash = hashes[1] % this->prime;
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
int RabinKarpSearch<Hash>::getWindowEnd()
{
    return this->currentWindowPosition + pattern.size() - 1;
}

template <typename Hash>
std::vector<int> RabinKarpSearch<Hash>::search()
{
    return std::vector<int>{patternHash, tmpHash};
}

template class RabinKarpSearch<StandardHash>;