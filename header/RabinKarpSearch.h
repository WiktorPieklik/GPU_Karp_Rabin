#ifndef GPU_KARP_RABIN_RABINKARPSEARCH_H
#define GPU_KARP_RABIN_RABINKARPSEARCH_H

#include "Hash/Hash.h"
#include "Text/Reader.h"
#include "Text/TextReaderFactory.h"

#include <vector>

class RabinKarpSearch
{
private:
    std::string file;
    std::string pattern;
    std::string text;

    std::unique_ptr<Reader> reader;

    long long patternHash{};
    long long windowHash{}; //moving window's hash
    size_t currentWindowPosition = 0;

    long long  mostSignificantWeight = 1;

    void calculateHashes();
    void init();
    void moveWindow();
    void calculateRollingHash();

public:
    RabinKarpSearch(std::string file, std::string pattern);
    std::vector<size_t> search();

};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_H
