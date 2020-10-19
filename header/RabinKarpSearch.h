#ifndef GPU_KARP_RABIN_RABINKARPSEARCH_H
#define GPU_KARP_RABIN_RABINKARPSEARCH_H

#include "Hash/Hash.h"
#include "Text/Reader.h"
#include "Text/TextReaderFactory.h"

template <typename Hash>
class RabinKarpSearch
{
private:
    std::string file;
    const std::string& pattern;
    std::vector<std::string> text;

    std::vector<size_t> matches;
    long long patternHash;
    long long windowHash; //moving window's hash
    size_t currentWindowPosition = 0; //starting lineNo
    size_t lineNo = 0; //line's number in input file (file is read line by line)

    const int prime = 23;
    const int base = 36; //input alphabet's length
    long long  mostSignificantWeight = 1;

    void calculateHashes();
    void init();
    void moveWindow();
    void calculateRollingHash();
    long long calculateHash(const std::string& text);
    std::vector<std::string> readText();

public:
    RabinKarpSearch(std::string file, const std::string& pattern);
    std::vector<size_t> search();

};


#endif //GPU_KARP_RABIN_RABINKARPSEARCH_H
